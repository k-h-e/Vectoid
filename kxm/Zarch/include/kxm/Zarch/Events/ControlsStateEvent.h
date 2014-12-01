//
//  ControlsStateEvent.h
//  kxm
//
//  Created by Kai Hergenröther on 11/10/14.
//
//


#ifndef KXM_ZARCH_CONTROLSSTATEEVENT_H_
#define KXM_ZARCH_CONTROLSSTATEEVENT_H_


#include <kxm/Zarch/ControlsState.h>
#include <kxm/Zarch/Events/ZarchEvent.h>


namespace kxm {
namespace Zarch {

class Physics;
class GameLogic;

class ControlsStateEvent : public ZarchEvent {
  public:
    ControlsStateEvent();
    ControlsStateEvent(const ControlsState &controlsState);
    const EventType &Type() const { return type; }
    void Serialize(Core::Buffer *targetBuffer) const;
    void Deserialize(Core::Buffer::Reader *bufferReader);
    void DispatchToPhysics(Physics *physics) const;
    void DispatchToGameLogic(GameLogic *gameLogic) const;
    
    static const EventType type;
    
    ControlsState controlsState;
};

}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_CONTROLSSTATEEVENT_H_

