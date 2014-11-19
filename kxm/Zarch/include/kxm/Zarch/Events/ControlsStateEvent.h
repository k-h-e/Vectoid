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

class ControlsStateEvent : public ZarchEvent {
  public:
    ControlsStateEvent();
    ControlsStateEvent(const ControlsState &controlsState);
    const EventType &Type() { return type; }
    void Serialize(Core::Buffer *targetBuffer) const;
    void Deserialize(Core::Buffer::Reader *bufferReader);
    
    static const EventType type;
    
    ControlsState controlsState_;
};

}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_CONTROLSSTATEEVENT_H_

