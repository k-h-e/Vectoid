//
//  EventHandlerInterface.h
//  kxm
//
//  Created by Kai Hergenröther on 10/8/12.
//
//


#ifndef KXM_GAME_EVENTHANDLERINTERFACE_H_
#define KXM_GAME_EVENTHANDLERINTERFACE_H_


#include <kxm/Core/Interface.h>


namespace kxm {
namespace Game {

//! Base interface to event handlers registered with the \ref EventQueue mechanism.
/*!
 *  \ingroup Game
 */
class EventHandlerInterface : public virtual Core::Interface {
};

//! Handles simple actor event types.
/*!
 *  \ingroup Game
 */
class ActorEventHandlerInterface : public virtual EventHandlerInterface {
};

//! Handles event types transporting vector information (next to an actor id).
/*!
 *  \ingroup Game
 */
class VectorEventHandlerInterface : public virtual EventHandlerInterface {
};

//! Handles event types transporting transform information (next to an actor id).
/*!
 *  \ingroup Game
 */
class TransformEventHandlerInterface : public virtual EventHandlerInterface {
};

}    // Namespace Game.
}    // Namespace kxm.


#endif    // KXM_GAME_EVENTHANDLERINTERFACE_H_
