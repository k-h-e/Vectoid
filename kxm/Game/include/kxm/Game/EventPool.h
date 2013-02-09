//
//  EventPool.h
//  kxm
//
//  Created by Kai Hergenröther on 11/29/12.
//
//


#ifndef KXM_GAME_EVENTPOOL_H_
#define KXM_GAME_EVENTPOOL_H_


#include <kxm/Core/ReusableItems.h>
#include <kxm/Game/EventPoolInterface.h>


namespace kxm {
namespace Game {

//! Adapter for \ref Pool<T>, so pool instances for different event types can be used with the
//! \ref EventQueueCore mechanism.
/*!
 *  \ingroup Game
 */
template<class T>
class EventPool : public virtual EventPoolInterface {
  public:
    EventPool() {}
    Event &Get(int *id) { return pool_.Get(id); }
    Event &Access(int id) { return pool_.Item(id); }
    void Put(int id) { pool_.Put(id); }
    
  private:
    EventPool(const EventPool &other);
    EventPool &operator=(const EventPool &other);
  
    Core::ReusableItems<T> pool_;
};

}    // Namespace Game.
}    // Namespace kxm.


#endif    // KXM_GAME_EVENTPOOL_H_

