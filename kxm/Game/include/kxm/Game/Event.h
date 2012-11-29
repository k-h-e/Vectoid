//
//  Event.h
//  kxm
//
//  Created by Kai Hergenröther on 11/29/12.
//
//

#ifndef KXM_GAME_EVENT_H_
#define KXM_GAME_EVENT_H_


namespace kxm {
namespace Game {

//! Base class to game events.
/*!
 *  \ingroup Game
 */
class Event {
  public:
    virtual ~Event() = 0;
};

}    // Namespace Game.
}    // Namespace kxm.


#endif    // KXM_GAME_EVENT_H_

