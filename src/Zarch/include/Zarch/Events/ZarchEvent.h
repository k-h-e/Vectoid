//
//  ZarchEvent.h
//  kxm
//
//  Created by Kai Hergenröther on 10/29/14.
//
//


#ifndef KXM_ZARCH_ZARCHEVENT_H_
#define KXM_ZARCH_ZARCHEVENT_H_


#include <Game/Event.h>


namespace kxm {
namespace Zarch {

class EventHandlerCore;

class ZarchEvent : public Game::Event {
  public:
    //! Makes the event dispatch itself to the specified handler.
    virtual void Dispatch(EventHandlerCore *handler) const = 0;
};

}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_ZARCHEVENT_H_

