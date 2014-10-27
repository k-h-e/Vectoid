//
//  EventQueueCore.h
//  kxm
//
//  Created by Kai Hergenröther on 11/29/12.
//
//


#ifndef KXM_GAME_EVENTQUEUECORE_H_
#define KXM_GAME_EVENTQUEUECORE_H_


#include <vector>
#include <memory>


namespace kxm {

namespace Core {
    class Buffer;
}

namespace Game {

class Event;
template<class T> class PoolInterface;
class EventHandlerInterface;

//! Event queue mechanism.
/*!
 *  \ingroup Game
 *
 *  Maintains in fact two event queues: \ref ScheduleEvent() adds events to the scheduling queue,
 *  wheras actual event processing as implemented by \ref ProcessEvents() happens on the processing
 *  queue. Note that while consuming the events in the processing queue, new events can be scheduled
 *  on the scheduling queue. Because we use two queues, event processing actually terminates for a
 *  given call to \ref ProcessEvents(), instead of running into an infinite loop.
 *
 *  The core mechanism uses non-negative integers to identify event types. \ref EventQueue<T> then
 *  provides a thin wrapper template so clients can use custom enum types instead.
 */
class EventQueueCore {
  public:
    EventQueueCore();
    //! Registers another event pool.
    int RegisterEventPool(std::shared_ptr<PoolInterface<Event>> pool);
    //! Registers another event type and associates it with the event pool that will be managing the
    //! event objects for that event type.
    void RegisterEventType(int eventType, int pool);
    //! Registers another handler for the specified event type.
    /*!
     *  Handlers will exclusively get called from \ref ProcessEvents().
     */
    void RegisterEventHandler(int eventType,
                              const std::shared_ptr<EventHandlerInterface> &eventHandler);
    //! Schedules a new event of the specified type on the scheduling queue and grants access to it
    //! so that the client can configure it before the next call to \ref ProcessEvents().
    /*!
     *  May get called when \ref ProcessEvents() is executing.
     */
    Event &ScheduleEvent(int eventType);
    //! Processes the events scheduled earlier.
    /*!
     *  Flips scheduling and processing queues before processing events.
     */
    void ProcessEvents();
    //! Serializes the currently scheduled events to the specified buffer, potentially appending to
    //! already present content.
    void SerializeScheduledEvents(Core::Buffer *targetBuffer);
    //! Deserializes events from the specified buffer and schedules them.
    /*!
     *  If the specified data contains invalid serialization data, the results are undefined.
     */
    void DeserializeAndScheduleEvents(const Core::Buffer &buffer);
    
  private:
    struct EventTypeInfo {
        int                                                 pool;
        std::vector<std::shared_ptr<EventHandlerInterface>> handlers;
        EventTypeInfo(int aPool) : pool(aPool) {}
    };
    struct EventInfo {
        int pool;
        int itemId;
        EventInfo(int aPool, int anItemId) : pool(aPool), itemId(anItemId) {}
    };
    EventQueueCore(const EventQueueCore &other);
    EventQueueCore &operator=(const EventQueueCore &other);
    
    std::vector<std::shared_ptr<PoolInterface<Event>>> pools_;
    std::vector<EventTypeInfo>                         eventTypes_;
    std::vector<EventInfo>                             events_[2];
    int                                                schedulingQueue_;
};

}    // Namespace Game.
}    // Namespace kxm.


#endif    // KXM_GAME_EVENTQUEUECORE_H_

