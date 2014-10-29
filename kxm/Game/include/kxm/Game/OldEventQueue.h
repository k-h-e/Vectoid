//
//  EventQueue.h
//  kxm
//
//  Created by Kai Hergenröther on 11/30/12.
//
//


#ifndef KXM_GAME_OLDEVENTQUEUE_H_
#define KXM_GAME_OLDEVENTQUEUE_H_


#include <kxm/Game/OldEventQueueCore.h>


namespace kxm {
namespace Game {

//! Event queue mechanism. Wraps \ref EventQueueCore to allow clients to use custom enums to
//! specify event types, instead of <c>int</c>s.
/*!
 *  \ingroup Game
 */
template<class T>
class OldEventQueue : private OldEventQueueCore {
  public:
    OldEventQueue() {}
    
    //! See \ref EventQueueCore::RegisterEventPool().
    int RegisterEventPool(std::shared_ptr<PoolInterface<OldEvent>> pool) {
        return OldEventQueueCore::RegisterEventPool(pool);
    }
    
    //! See \ref EventQueueCore::RegisterEventType().
    void RegisterEventType(T eventType, int pool) {
        OldEventQueueCore::RegisterEventType((int)eventType, pool);
    }
    
    //! See \ref EventQueueCore::RegisterEventHandler().
    void RegisterEventHandler(T eventType,
                              const std::shared_ptr<EventHandlerInterface> &eventHandler) {
        OldEventQueueCore::RegisterEventHandler((int)eventType, eventHandler);
    }
    
    //! See \ref EventQueueCore::ScheduleEvent().
    OldEvent &ScheduleEvent(T eventType) {
        return OldEventQueueCore::ScheduleEvent((int)eventType);
    }
    
    //! Same as \ref ScheduleEvent(), but <c>static_cast</c>s to the specified event type, for
    //! convenience.
    template<class EventType> EventType &ScheduleEvent(T eventType) {
        return static_cast<EventType &>(OldEventQueueCore::ScheduleEvent((int)eventType));
    }
    
    //! See \ref EventQueueCore::ProcessEvents().
    void ProcessEvents() {
        OldEventQueueCore::ProcessEvents();
    }
    
    //! See \ref EventQueueCore::SerializeScheduledEvents().
    void SerializeScheduledEvents(Core::Buffer *targetBuffer) {
        OldEventQueueCore::SerializeScheduledEvents(targetBuffer);
    }
    
    //! See \ref EventQueueCore::DeserializeAndScheduleEvents().
    void DeserializeAndScheduleEvents(const Core::Buffer &buffer) {
        OldEventQueueCore::DeserializeAndScheduleEvents(buffer);
    }
    
  private:
    OldEventQueue(const OldEventQueue &other);
    OldEventQueue &operator=(const OldEventQueue &other);
};

}    // Namespace Game.
}    // Namespace kxm.


#endif    // KXM_GAME_OLDEVENTQUEUE_H_
