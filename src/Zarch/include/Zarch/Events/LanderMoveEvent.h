//
//  LanderMoveEvent.h
//  kxm
//
//  Created by Kai Hergenröther on 11/10/14.
//
//


#ifndef KXM_ZARCH_LANDERMOVEEVENT_H_
#define KXM_ZARCH_LANDERMOVEEVENT_H_


#include <Vectoid/Transform.h>
#include <Zarch/Events/ZarchEvent.h>


namespace kxm {
namespace Zarch {

class Video;

class LanderMoveEvent : public ZarchEvent {
  public:
    LanderMoveEvent();
    LanderMoveEvent(const Vectoid::Transform &newLanderTransform);
    const EventType &Type() const { return type; }
    void Serialize(Core::Buffer *targetBuffer) const;
    void Deserialize(Core::Buffer::Reader *bufferReader);
    void DispatchToVideo(Video *video) const;
    
    static const EventType type;
    
    Vectoid::Transform newLanderTransform;
};

}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_LANDERMOVEEVENT_H_

