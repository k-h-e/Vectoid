//
//  FrameTimeEvent.h
//  kxm
//
//  Created by Kai Hergenröther on 10/29/14.
//
//


#ifndef KXM_ZARCH_FRAMETIMEEVENT_H_
#define KXM_ZARCH_FRAMETIMEEVENT_H_


#include <Zarch/Events/ZarchEvent.h>


namespace kxm {
namespace Zarch {

class Video;
class Physics;

class FrameTimeEvent : public ZarchEvent {
  public:
    FrameTimeEvent();
    FrameTimeEvent(float timeS);
    const EventType &Type() const { return type; }
    void Serialize(Core::Buffer *targetBuffer) const;
    void Deserialize(Core::Buffer::Reader *bufferReader);
    void Dispatch(EventHandlerCore *handler) const;
    
    static const EventType type;
    
    float timeS;
};

}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_FRAMETIMEEVENT_H_

