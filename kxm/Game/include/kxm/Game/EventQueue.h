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
class EventQueue : private EventQueueCore {
  public:
    EventQueue() {}
    
    //! See \ref EventQueueCore::RegisterEventPool().
    int RegisterEventPool(boost::shared_ptr<PoolInterface<Event> > pool) {
        return EventQueueCore::RegisterEventPool(pool);
    }
  
    //! See \ref EventQueueCore::RegisterEventType().
    void RegisterEventType(T eventType, int pool) {
        EventQueueCore::RegisterEventType((int)eventType, pool);
    }
    
    //! See \ref EventQueueCore::RegisterEventHandler().
    void RegisterEventHandler(T eventType, EventHandlerInterface *eventHandler) {
        EventQueueCore::RegisterEventHandler((int)eventType, eventHandler);
    }
    
    //! See \ref EventQueueCore::ScheduleEvent().
    Event &ScheduleEvent(T eventType) {
        return EventQueueCore::ScheduleEvent((int)eventType);
    }
    
    //! See \ref EventQueueCore::ProcessEvents().
    void ProcessEvents() {
        EventQueueCore::ProcessEvents();
    }
    
  private:
    EventQueue(const EventQueue &other);
    EventQueue &operator=(const EventQueue &other);
};

}    // Namespace Game.
}    // Namespace kxm.


#endif    // KXM_GAME_EVENTQUEUE_H_
