//
//  LanderVelocityEvent.h
//  kxm
//
//  Created by Kai Hergenröther on 11/10/14.
//
//

#ifndef KXM_ZARCH_LANDERVELOCITYEVENT_H_
#define KXM_ZARCH_LANDERVELOCITYEVENT_H_


#include <Vectoid/Vector.h>
#include <Zarch/Events/ZarchEvent.h>


namespace kxm {
namespace Zarch {

class Video;

class LanderVelocityEvent : public ZarchEvent {
  public:
    LanderVelocityEvent();
    LanderVelocityEvent(const Vectoid::Vector &velocity);
    const EventType &Type() const { return type; }
    void Serialize(Core::Buffer *targetBuffer) const;
    void Deserialize(Core::Buffer::Reader *bufferReader);
    void DispatchToVideo(Video *video) const;
    
    static const EventType type;
    
    Vectoid::Vector velocity;
};

}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_LANDERVELOCITYEVENT_H_

