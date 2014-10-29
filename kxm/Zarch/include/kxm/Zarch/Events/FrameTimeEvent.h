//
//  FrameTimeEvent.h
//  kxm
//
//  Created by Kai Hergenröther on 10/29/14.
//
//


#ifndef KXM_ZARCH_FRAMETIMEEVENT_H_
#define KXM_ZARCH_FRAMETIMEEVENT_H_


#include <kxm/Zarch/Events/ZarchEvent.h>


namespace kxm {
namespace Zarch {

class FrameTimeEvent : public ZarchEvent {
  public:
    const EventType &Type() { return type; }
    void Serialize(Core::Buffer *targetBuffer);
    void Deserialize(Core::Buffer::Reader *bufferReader);
    
  private:
    static const EventType type;
};

}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_FRAMETIMEEVENT_H_

