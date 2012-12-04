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
#include <deque>

#include <boost/shared_ptr.hpp>


namespace kxm {
namespace Game {

class Event;
class EventPoolInterface;
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
    ~EventQueueCore();
    //! Registers another event type with the event queue, together with an event pool that will
    //! be managing the event objects for that event type.
    void RegisterEventType(int eventType, boost::shared_ptr<EventPoolInterface> pool);
    //! Registers another handler for the specified event type.
    /*!
     *  The handler will be registered as a weak reference. Handlers will exclusively get accessed
     *  from \ref ProcessEvents().
     */
    void RegisterEventHandler(int eventType, EventHandlerInterface *eventHandler);
    //! Schedules a new event of the specified type on the scheduling queue and grants access to it
    //! so that the client can configure it before the next call to \ref ProcessEvents().
    /*!
     *  May get called by event handlers registered with this event queue.
     */
    Event *ScheduleEvent(int eventType);
    //! Flips scheduling and processing queues and processes the events in the (new) processing
    //! queue.
    void ProcessEvents();
    
  private:
    EventQueueCore(const EventQueueCore &other);
    EventQueueCore &operator=(const EventQueueCore &other);
    
    std::vector<boost::shared_ptr<EventPoolInterface> > pools_;    // Even faster than a hash map.
    std::vector<std::vector<EventHandlerInterface *> >  handlers_; // Weak references.
    std::deque<Event *>                                 queues_[2];
    int                                                 schedulingQueue_;
};

}    // Namespace Game.
}    // Namespace kxm.


#endif    // KXM_GAME_EVENTQUEUECORE_H_

