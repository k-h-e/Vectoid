//
//  events.h
//  kxm
//
//  Created by Kai Hergenröther on 11/30/12.
//
//


#ifndef KXM_ZARCH_EVENTS_H_
#define KXM_ZARCH_EVENTS_H_


#include <kxm/Game/Event.h>


namespace kxm {
namespace Zarch {

class ZarchEvent : public Game::Event {
  public:
    enum Type { ActorEvent,
                PositionEvent };
};

class ActorEvent : public ZarchEvent {
};

class PositionEvent : public ZarchEvent {
};

}    // Namespace Zarch.
}    // Namespace kxm.


#endif    // KXM_ZARCH_EVENTS_H_
