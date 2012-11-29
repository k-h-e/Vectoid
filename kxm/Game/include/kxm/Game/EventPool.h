//
//  EventPool.h
//  kxm
//
//  Created by Kai Hergenröther on 11/29/12.
//
//


#ifndef KXM_GAME_EVENTPOOL_H_
#define KXM_GAME_EVENTPOOL_H_


namespace kxm {
namespace Game {

//! Adapter for \ref Pool<T>, so Pool instances for different event types can be used with the
//! \ref EventQueueCore mechanism.
/*!
 *  \ingroup Game
 */
template<class T>
class EventPool {
  public:
    Event *Get();
    void Put(Event *event);
    
  private:
    Pool<T> pool_;
};

Event *EventPool::Get() {
    return pool_.Get();
}

void EventPool::Put(Event *event) {
    pool_.Put(static_cast<T *>(event));
}

}    // Namespace Game.
}    // Namespace kxm.


#endif    // KXM_GAME_EVENTPOOL_H_

