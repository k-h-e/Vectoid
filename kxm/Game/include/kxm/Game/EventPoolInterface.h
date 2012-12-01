//
//  EventPoolInterface.h
//  kxm
//
//  Created by Kai Hergenröther on 11/30/12.
//
//


#ifndef KXM_GAME_EVENTPOOLINTERFACE_H_
#define KXM_GAME_EVENTPOOLINTERFACE_H_


#include <kxm/Core/Interface.h>


namespace kxm {
namespace Game {

class Event;

//! Allows that event pool instances for different event types can be used with the
//! \ref EventQueueCore mechanism.
/*!
 *  \ingroup Game
 */
class EventPoolInterface : public virtual Core::Interface {
  public:
    virtual Event *Get() = 0;
    virtual void Put(Event *event) = 0;
};

}    // Namespace Game.
}    // Namespace kxm.


#endif    // KXM_GAME_EVENTPOOLINTERFACE_H_
