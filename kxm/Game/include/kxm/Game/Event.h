//
//  Event.h
//  kxm
//
//  Created by Kai Hergenröther on 11/29/12.
//
//

#ifndef KXM_GAME_EVENT_H_
#define KXM_GAME_EVENT_H_


#include <kxm/Core/Interface.h>


namespace kxm {
namespace Game {

//! Base class to game events.
/*!
 *  \ingroup Game
 *
 *  Events exclusively contain "data" fields and never directly reference any other objects. If the
 *  data describes aspects of an actor, the actor is identified via a non-negative integer actor id.
 */
class Event : public virtual Core::Interface {
  public:
    Event() : type_(-1) {}
    
  protected:
    int type_;
    
  private:
    friend class EventQueueCore;
};

}    // Namespace Game.
}    // Namespace kxm.


#endif    // KXM_GAME_EVENT_H_

