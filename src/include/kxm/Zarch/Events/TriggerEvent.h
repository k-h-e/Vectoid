#ifndef KXM_ZARCH_TRIGGEREVENT_H_
#define KXM_ZARCH_TRIGGEREVENT_H_

#include <kxm/Zarch/Events/ZarchEvent.h>

namespace kxm {
namespace Zarch {

//! Trigger event.
/*!
 *  \ingroup ZarchEvents
 */
class TriggerEvent : public ZarchEvent {
  public:
    enum Trigger { NoTrigger,
                   AITrigger,
                   GameLogicTrigger,
                   PhysicsTrigger,
                   SimulationUpdatedTrigger,
                   FrameRenderedTrigger };
  
    TriggerEvent();
    //! Takes trigger type and time in seconds since the last trigger of this type.
    TriggerEvent(Trigger aTrigger, float aDeltaTime_s);
    const EventType &Type() const { return type; }
    void Serialize(Core::Buffer *targetBuffer) const;
    void Deserialize(Core::Buffer::Reader *bufferReader);
    void Dispatch(EventHandlerCore *handler) const;
    
    static const EventType type;
    
    Trigger trigger;
    float   deltaTime_s;
};

}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_TRIGGEREVENT_H_

