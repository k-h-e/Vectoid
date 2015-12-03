#ifndef KXM_GAME_EVENTQUEUE_H_
#define KXM_GAME_EVENTQUEUE_H_


#include <vector>
#include <memory>
#include <unordered_map>

#include <Game/Event.h>
#include <Game/EventQueueSchedulingInterface.h>
#include <Game/EventHandlerInterface.h>
#include <Game/EventQueueHub.h>

namespace kxm {

namespace Core {
    class Buffer;
}

namespace Game {

class Event;

//! Event queue mechanism.
/*!
 *  Internally, there are in fact two queues: the active queue and the schedule queue. New events
 *  get enqueued on the schedule queue using \ref Schedule(), and processing happens on the active
 *  queue using \ref ProcessEvents(). Queue swapping happens automatically.
 */
class EventQueue : public EventQueueSchedulingInterface {
  public:
    //! Hub may be 0-handle if no hub is used.
    EventQueue(int initialBufferSize, std::shared_ptr<EventQueueHub> hub, bool hubSyncWaitEnabled);
    EventQueue(const EventQueue &other)             = delete;
    EventQueue &operator=(const EventQueue &other)  = delete;
    EventQueue(const EventQueue &&other)            = delete;
    EventQueue &operator=(const EventQueue &&other) = delete;
    //! Registers the specified event.
    void RegisterEvent(std::unique_ptr<Event> protoType);
    //! Registers a handler for the specified event, as weak reference.
    /*!
     *  A given handler must be registered for a given event only once.
     */
    void RegisterHandler(const Event::EventType &eventType, EventHandlerInterface *handler);
    //! Unregisters the specified event handler from whatever event it is registered for.
    void UnregisterHandler(EventHandlerInterface *handler);
    //! Processes all events in the active queue by invoking the respective handlers.
    /*!
     *  While processing the events in the active queue and activating their event
     *  handlers, the event queue is prepared to get all methods called that it exposes via the
     *  EventQueueSchedulingInterface. All other public methods on the other hand must not get
     *  called while ProcessEvents() executes.
     *
     *  \return
     *  <c>false</c> in case a hub is used and shutdown has been requested.
     */
    bool ProcessEvents();
    
    void Schedule(const Event &event);
        
  private:
    struct EventInfo {
        std::unique_ptr<Event>               prototype;
        std::vector<EventHandlerInterface *> handlers;
        EventInfo(std::unique_ptr<Event> proto) : prototype(std::move(proto)) {}
    };
    
    std::vector<EventInfo>               events_;
    std::unordered_map<size_t, int>      idToSlotMap_;
    std::unique_ptr<Core::Buffer>        scheduleQueue_,
                                         activeQueue_;
    std::shared_ptr<EventQueueHub>       hub_;
    EventQueueHub::ClientId              hubClientId_;
    bool                                 processingEvents_,
                                         hubSyncWaitEnabled_;
};

}    // Namespace Game.
}    // Namespace kxm.

#endif    // KXM_GAME_EVENTQUEUE_H_
