//
//  EventQueue.h
//  kxm
//
//  Created by Kai Hergenröther on 11/30/12.
//
//


#ifndef KXM_GAME_EVENTQUEUE_H_
#define KXM_GAME_EVENTQUEUE_H_


#include <kxm/Game/EventQueueCore.h>


namespace kxm {
namespace Game {

//! Event queue mechanism. Wraps \ref EventQueueCore to allow clients to use custom enums to
//! specify event types, instead of <c>int</c>s.
/*!
 *  \ingroup Game
 */
template<class T>
class EventQueue : public EventQueueCore {
  public:
    //! Registers another event type with the event queue, together with an event pool that will
    //! be managing the event objects for that event type.
    void RegisterEventType(T eventType, boost::shared_ptr<EventPoolInterface> pool);
    //! Schedules a new event of the specified type on the scheduling queue and grants access to it
    //! so that the client can configure it before the next call to \ref ProcessEvents().
    Event *ScheduleEvent(T eventType);
};

template<class T>
void EventQueue<T>::RegisterEventType(T eventType, boost::shared_ptr<EventPoolInterface> pool) {
    EventQueueCore::RegisterEventType((int)eventType, pool);
}

template<class T>
Event *EventQueue<T>::ScheduleEvent(T eventType) {
    return EventQueueCore::ScheduleEvent((int)eventType);
}

}    // Namespace Game.
}    // Namespace kxm.


#endif    // KXM_GAME_EVENTQUEUE_H_
