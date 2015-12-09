#ifndef KXM_GAME_EVENTQUEUE_H_
#define KXM_GAME_EVENTQUEUE_H_


#include <assert.h>
#include <vector>
#include <memory>
#include <unordered_map>

#include <kxm/Core/logging.h>
#include <kxm/Core/Buffer.h>
#include <Game/Event.h>
#include <Game/EventQueueClientInterface.h>
#include <Game/EventQueueHub.h>

namespace kxm {
namespace Game {


//! Event queue mechanism.
/*!
 *  Internally, there are in fact two queues: the active queue and the schedule queue. New events
 *  get enqueued on the schedule queue using \ref Schedule(), and processing happens on the active
 *  queue using \ref ProcessEvents(). Queue swapping happens automatically.
 *
 *  <c>EventClass</c> must derive from <c>Event</c> and implement a method
 *  <c>void Dispatch(EventHandlerClass *handler) const</c>.
 *
 *  \ingroup Game
 */
template<class EventClass, class EventHandlerClass>
class EventQueue : public virtual EventQueueClientInterface<EventClass> {
  public:
    //! Hub may be 0-handle if no hub is used.
    EventQueue(int initialBufferSize, std::shared_ptr<EventQueueHub> hub, bool hubSyncWaitEnabled);
    EventQueue(const EventQueue &other)             = delete;
    EventQueue &operator=(const EventQueue &other)  = delete;
    EventQueue(const EventQueue &&other)            = delete;
    EventQueue &operator=(const EventQueue &&other) = delete;
    //! Registers the specified event.
    void RegisterEvent(std::unique_ptr<EventClass> protoType);
    //! Registers a handler for the specified event, as weak reference.
    /*!
     *  A given handler must be registered for a given event only once.
     */
    void RegisterHandler(const Event::EventType &eventType, EventHandlerClass *handler);
    //! Unregisters the specified event handler from whatever event it is registered for.
    void UnregisterHandler(EventHandlerClass *handler);
    //! Processes all events in the active queue by invoking the respective handlers.
    /*!
     *  Only while this method is executing will event handlers get called.
     *
     *  While processing the events in the active queue and activating their event
     *  handlers, the event queue is prepared to get all methods called that it exposes via the
     *  EventQueueClientInterface. All other public methods on the other hand must not get
     *  called while ProcessEvents() executes.
     *
     *  \return
     *  <c>false</c> in case a hub is used and shutdown has been requested.
     */
    bool ProcessEvents();
    
    void Schedule(const EventClass &event);
        
  private:
    struct EventInfo {
        std::unique_ptr<EventClass>      prototype;
        std::vector<EventHandlerClass *> handlers;
        EventInfo(std::unique_ptr<EventClass> proto) : prototype(std::move(proto)) {}
    };
    
    std::vector<EventInfo>           events_;
    std::unordered_map<size_t, int>  idToSlotMap_;
    std::unique_ptr<Core::Buffer>    scheduleQueue_,
                                     activeQueue_;
    std::shared_ptr<EventQueueHub>   hub_;
    int                              hubClientId_,
                                     hubWaitSeqNo_;
    bool                             processingEvents_,
                                     hubSyncWaitEnabled_;
};

template<class EventClass, class EventHandlerClass>
EventQueue<EventClass, EventHandlerClass>::EventQueue(
        int initialBufferSize, std::shared_ptr<EventQueueHub> hub, bool hubSyncWaitEnabled)
    : activeQueue_(new kxm::Core::Buffer(initialBufferSize >= 16 ? initialBufferSize : 16)),
      scheduleQueue_(new kxm::Core::Buffer(initialBufferSize >= 16 ? initialBufferSize : 16)),
      hub_(hub),
      hubClientId_(!hub ? 0 : hub->AddClient()),
      hubWaitSeqNo_(0),
      processingEvents_(false),
      hubSyncWaitEnabled_(hubSyncWaitEnabled) {
    // Nop.
}

template<class EventClass, class EventHandlerClass>
void EventQueue<EventClass, EventHandlerClass>::RegisterEvent(
        std::unique_ptr<EventClass> protoType) {
    assert(!processingEvents_);
    assert(protoType.get() != nullptr);
    size_t id             = protoType->Type().id;
    bool   alreadyPresent = (idToSlotMap_.find(id) != idToSlotMap_.end());
    if (alreadyPresent)
        kxm::Core::Log().Stream() << "hash collision while registering event \""
                                  << protoType->Type().name << "\"" << std::endl;
    assert(!alreadyPresent);
    int slot = (int)events_.size();
    events_.push_back(EventInfo(std::move(protoType)));
    idToSlotMap_[id] = slot;
}

template<class EventClass, class EventHandlerClass>
void EventQueue<EventClass, EventHandlerClass>::RegisterHandler(
        const Event::EventType &eventType, EventHandlerClass *handlerToRegister) {
    assert(!processingEvents_);
    auto infoIter = idToSlotMap_.find(eventType.id);
    assert(infoIter != idToSlotMap_.end());
    for (EventHandlerClass *handler : events_[infoIter->second].handlers) {
        assert(handler != handlerToRegister);
    }
    events_[infoIter->second].handlers.push_back(handlerToRegister);
}

template<class EventClass, class EventHandlerClass>
void EventQueue<EventClass, EventHandlerClass>::UnregisterHandler(
        EventHandlerClass *handlerToUnregister) {
    assert(!processingEvents_);
    for (auto &info : events_) {
        std::vector<EventHandlerClass *> handlers;
        for (EventHandlerClass *handler : info.handlers) {
            if (handler != handlerToUnregister) {
                handlers.push_back(handler);
            }
        }
        info.handlers = handlers;
    }
}

// Might get called while ProcessEvents() executes.
template<class EventClass, class EventHandlerClass>
void EventQueue<EventClass, EventHandlerClass>::Schedule(const EventClass &event) {
    int slot = idToSlotMap_[event.Type().id];
    scheduleQueue_->Append(&slot, sizeof(slot));
    event.Serialize(scheduleQueue_.get());
}

template<class EventClass, class EventHandlerClass>
bool EventQueue<EventClass, EventHandlerClass>::ProcessEvents() {
    assert(!processingEvents_);
    processingEvents_ = true;
    
    bool terminationRequested = false;
    if (hub_.get()) {
        terminationRequested = !hub_->Sync(hubClientId_, &scheduleQueue_,
                                           hubSyncWaitEnabled_ ? &hubWaitSeqNo_ : nullptr);
    }
    activeQueue_->Clear();
    activeQueue_.swap(scheduleQueue_);
        
    int slot;
    kxm::Core::Buffer::Reader reader = activeQueue_->GetReader();
    while (reader.ReadBlock(&slot, sizeof(slot))) {
        EventInfo  &info  = events_[slot];
        EventClass &event = *(info.prototype);
        event.Deserialize(&reader);
        for (EventHandlerClass *handler : info.handlers) {
            event.Dispatch(handler);
        }
    }
    
    processingEvents_ = false;
    return !terminationRequested;
}

}    // Namespace Game.
}    // Namespace kxm.

#endif    // KXM_GAME_EVENTQUEUE_H_
