//
//  EventHandlerInterface.h
//  kxm
//
//  Created by Kai Hergenröther on 12/3/12.
//
//


#ifndef KXM_GAME_EVENTHANDLERINTERFACE_H_
#define KXM_GAME_EVENTHANDLERINTERFACE_H_


#include <kxm/Core/Interface.h>


namespace kxm {
namespace Game {

class Event;
class OldEvent;

class EventHandlerInterface : public virtual Core::Interface {
  public:
    //! Makes the handler handle the specified event.
    virtual void HandleEvent(const Event &event) = 0;
    //! Makes the handler handle the specified event.
    virtual void HandleEvent(const OldEvent &event) = 0;
};

}    // Namespace Game.
}    // Namespace kxm.


#endif    // KXM_GAME_EVENTHANDLERINTERFACE_H_
