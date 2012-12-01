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
 */
class Event : public virtual Core::Interface {
  public:
    Event() : type_(-1) {}
    
  private:
    friend class EventQueueCore;
    int type_;
};

}    // Namespace Game.
}    // Namespace kxm.


#endif    // KXM_GAME_EVENT_H_

