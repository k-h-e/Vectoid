//
//  ControlsStateEvent.h
//  kxm
//
//  Created by Kai Hergenröther on 11/10/14.
//
//


#ifndef KXM_ZARCH_CONTROLSSTATEEVENT_H_
#define KXM_ZARCH_CONTROLSSTATEEVENT_H_


#include <kxm/Zarch/Events/ZarchEvent.h>


namespace kxm {
namespace Zarch {

class ControlsStateEvent : public ZarchEvent {
  public:
    const EventType &Type() { return type; }
    void Serialize(Core::Buffer *targetBuffer);
    void Deserialize(Core::Buffer::Reader *bufferReader);
    
    static const EventType type;
};

}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_CONTROLSSTATEEVENT_H_

