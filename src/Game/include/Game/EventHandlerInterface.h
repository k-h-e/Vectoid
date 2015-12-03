//
//  EventHandlerInterface.h
//  kxm
//
//  Created by Kai Hergenröther on 12/3/12.
//
//


#ifndef KXM_GAME_EVENTHANDLERINTERFACE_H_
#define KXM_GAME_EVENTHANDLERINTERFACE_H_


#include <memory>

#include <kxm/Core/Interface.h>
#include <Game/Event.h>


namespace kxm {
namespace Game {

//! Interface to event handlers.
/*!
 *  \ingroup Game
 */
class EventHandlerInterface : public virtual Core::Interface {
  public:
    //! Makes the handler handle the specified event.
    virtual void HandleEvent(const Event &event) = 0;
    //! Informs about the events handled by the event handler.
    virtual std::vector<Event::EventType> EnumerateHandledEvents() = 0;
};

}    // Namespace Game.
}    // Namespace kxm.


#endif    // KXM_GAME_EVENTHANDLERINTERFACE_H_
