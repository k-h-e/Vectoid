#ifndef KXM_GAME_EVENTLOOP_H_
#define KXM_GAME_EVENTLOOP_H_

#include <assert.h>
#include <vector>
#include <memory>
#include <unordered_map>

#include <kxm/Core/logging.h>
#include <kxm/Core/Buffer.h>
#include <Game/Event.h>
#include <Game/EventLoopHub.h>

namespace kxm {
namespace Game {

//! Event loop.
/*!
 *  The \ref EventLoop s of multiple threads are integrated using an \ref EventLoopHub.
 *
 *  <c>EventClass</c> must derive from <c>Event</c> and implement a method
 *  <c>void Dispatch(EventHandlerClass *handler) const</c>.
 *
 *  \ingroup Game
 */
template<class EventClass, class EventHandlerClass>
class EventLoop {
  public:
    EventLoop(std::shared_ptr<EventLoopHub> hub);
    EventLoop(const EventLoop &other)             = delete;
    EventLoop &operator=(const EventLoop &other)  = delete;
    EventLoop(const EventLoop &&other)            = delete;
    EventLoop &operator=(const EventLoop &&other) = delete;
    //! Registers the specified event.
    void RegisterEvent(std::unique_ptr<EventClass> protoType);
    //! Registers a handler for the specified event, as a weak reference.
    /*!
     *  A given handler must be registered for a given event only once.
     */
    void RegisterHandler(const Event::EventType &eventType, EventHandlerClass *handler);
    //! Unregisters the specified event handler from whatever event it is registered for.
    void UnregisterHandler(EventHandlerClass *handler);
    //! Runs the event loop, invoking handlers for events as they arrive.
    void Run();
    //! Schedules the specified event for execution on the loop.
    /*!
     *  This is the only method that may be called while \ref Run() executes, that is: from event handlers invoked by
     *  the loop.
     */
    void Schedule(const EventClass &event);
        
  private:
    struct EventInfo {
        std::unique_ptr<EventClass>      prototype;
        std::vector<EventHandlerClass *> handlers;
        EventInfo(std::unique_ptr<EventClass> proto) : prototype(std::move(proto)) {}
    };
    
    std::vector<EventInfo>          events_;
    std::unordered_map<size_t, int> idToSlotMap_;
    std::unique_ptr<Core::Buffer>   eventsToSchedule_;
    std::shared_ptr<EventLoopHub>   hub_;
    int                             hubClientId_;
    bool                            running_;
};

template<class EventClass, class EventHandlerClass>
EventLoop<EventClass, EventHandlerClass>::EventLoop(std::shared_ptr<EventLoopHub> hub)
    : eventsToSchedule_(new kxm::Core::Buffer()),
      hub_(hub),
      hubClientId_(hub->AddEventLoop()),
      running_(false) {
    // Nop.
}

template<class EventClass, class EventHandlerClass>
void EventLoop<EventClass, EventHandlerClass>::RegisterEvent(std::unique_ptr<EventClass> protoType) {
    assert(!running_);
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
void EventLoop<EventClass, EventHandlerClass>::RegisterHandler(const Event::EventType &eventType,
                                                               EventHandlerClass *handlerToRegister) {
    assert(!running_);
    auto infoIter = idToSlotMap_.find(eventType.id);
    assert(infoIter != idToSlotMap_.end());
    for (EventHandlerClass *handler : events_[infoIter->second].handlers) {
        assert(handler != handlerToRegister);
    }
    events_[infoIter->second].handlers.push_back(handlerToRegister);
}

template<class EventClass, class EventHandlerClass>
void EventLoop<EventClass, EventHandlerClass>::UnregisterHandler(EventHandlerClass *handlerToUnregister) {
    assert(!running_);
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

template<class EventClass, class EventHandlerClass>
void EventLoop<EventClass, EventHandlerClass>::Run() {
    assert(!running_);
    running_ = true;
    
    std::unique_ptr<kxm::Core::Buffer> buffer(new kxm::Core::Buffer());
    while (!hub_->GetEvents(hubClientId_, &buffer)) {
        kxm::Core::Buffer::Reader reader = buffer->GetReader();
        int slot;
        while (reader.ReadBlock(&slot, sizeof(slot))) {
            EventInfo  &info  = events_[slot];
            EventClass &event = *(info.prototype);
            event.Deserialize(&reader);
            for (EventHandlerClass *handler : info.handlers) {
                event.Dispatch(handler);
            }
        }
    }
    
    running_ = false;
}

template<class EventClass, class EventHandlerClass>
void EventLoop<EventClass, EventHandlerClass>::Schedule(const EventClass &event) {
    int slot = idToSlotMap_[event.Type().id];
    eventsToSchedule_->Append(&slot, sizeof(slot));
    event.Serialize(eventsToSchedule_.get());
    hub_->ScheduleEvents(eventsToSchedule_);
    eventsToSchedule_->Clear();
}
    
}    // Namespace Game.
}    // Namespace kxm.

#endif    // KXM_GAME_EVENTLOOP_H_
