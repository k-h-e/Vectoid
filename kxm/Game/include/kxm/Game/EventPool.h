//
//  EventPool.h
//  kxm
//
//  Created by Kai Hergenröther on 11/29/12.
//
//


#ifndef KXM_GAME_EVENTPOOL_H_
#define KXM_GAME_EVENTPOOL_H_


#include <kxm/Core/Pool.h>
#include <kxm/Game/EventPoolInterface.h>


namespace kxm {
namespace Game {

//! Adapter for \ref Pool<T>, so Pool instances for different event types can be used with the
//! \ref EventQueueCore mechanism.
/*!
 *  \ingroup Game
 */
template<class T>
class EventPool : public virtual EventPoolInterface {
  public:
    EventPool();
    Event *Get();
    void Put(Event *event);
    
  private:
    EventPool(const EventPool &other);
    EventPool &operator=(const EventPool &other);
  
    Core::Pool<T> pool_;
};

template<class T>
EventPool<T>::EventPool() {
}

template<class T>
Event *EventPool<T>::Get() {
    return pool_.Get();
}

template<class T>
void EventPool<T>::Put(Event *event) {
    pool_.Put(static_cast<T *>(event));
}

}    // Namespace Game.
}    // Namespace kxm.


#endif    // KXM_GAME_EVENTPOOL_H_

