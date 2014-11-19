//
//  LanderMoveEvent.h
//  kxm
//
//  Created by Kai Hergenröther on 11/10/14.
//
//


#ifndef KXM_ZARCH_LANDERMOVEEVENT_H_
#define KXM_ZARCH_LANDERMOVEEVENT_H_


#include <kxm/Vectoid/Transform.h>
#include <kxm/Zarch/Events/ZarchEvent.h>


namespace kxm {
namespace Zarch {

class LanderMoveEvent : public ZarchEvent {
  public:
    LanderMoveEvent();
    LanderMoveEvent(const Vectoid::Transform &newLanderTransform);
    const EventType &Type() { return type; }
    void Serialize(Core::Buffer *targetBuffer) const;
    void Deserialize(Core::Buffer::Reader *bufferReader);
    
    static const EventType type;
    
    Vectoid::Transform newLanderTransform_;
};

}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_LANDERMOVEEVENT_H_

