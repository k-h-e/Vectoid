//
//  LanderThrusterEvent.h
//  kxm
//
//  Created by Kai Hergenröther on 11/10/14.
//
//

#ifndef KXM_ZARCH_LANDERTHRUSTEREVENT_H_
#define KXM_ZARCH_LANDERTHRUSTEREVENT_H_


#include <kxm/Zarch/Events/ZarchEvent.h>


namespace kxm {
namespace Zarch {

class LanderThrusterEvent : public ZarchEvent {
  public:
    LanderThrusterEvent();
    LanderThrusterEvent(bool thrusterEnabled);
    const EventType &Type() { return type; }
    void Serialize(Core::Buffer *targetBuffer) const;
    void Deserialize(Core::Buffer::Reader *bufferReader);
    
    static const EventType type;
    
    bool thrusterEnabled_;
};

}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_LANDERTHRUSTEREVENT_H_

