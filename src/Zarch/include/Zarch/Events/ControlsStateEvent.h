//
//  ControlsStateEvent.h
//  kxm
//
//  Created by Kai Hergenröther on 11/10/14.
//
//


#ifndef KXM_ZARCH_CONTROLSSTATEEVENT_H_
#define KXM_ZARCH_CONTROLSSTATEEVENT_H_


#include <Zarch/ControlsState.h>
#include <Zarch/Events/ZarchEvent.h>


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
    void Dispatch(EventHandlerCore *handler) const;
    
    static const EventType type;
    
    ControlsState controlsState;
};

}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_CONTROLSSTATEEVENT_H_

