//
//  LanderThrusterEvent.h
//  kxm
//
//  Created by Kai Hergenröther on 11/10/14.
//
//

#ifndef KXM_ZARCH_LANDERTHRUSTEREVENT_H_
#define KXM_ZARCH_LANDERTHRUSTEREVENT_H_


#include <Zarch/Events/ZarchEvent.h>


namespace kxm {
namespace Zarch {

//! Lander thruster event.
/*!
 *  \ingroup ZarchEvents
 */
class LanderThrusterEvent : public ZarchEvent {
  public:
    LanderThrusterEvent();
    LanderThrusterEvent(bool thrusterEnabled);
    const EventType &Type() const { return type; }
    void Serialize(Core::Buffer *targetBuffer) const;
    void Deserialize(Core::Buffer::Reader *bufferReader);
    void Dispatch(EventHandlerCore *handler) const;
    
    static const EventType type;
    
    bool thrusterEnabled;
};

}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_LANDERTHRUSTEREVENT_H_

