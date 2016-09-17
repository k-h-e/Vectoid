#ifndef KXM_ZARCH_ACCELERATIONEVENT_H_
#define KXM_ZARCH_ACCELERATIONEVENT_H_

#include <kxm/Game/ActorName.h>
#include <kxm/Vectoid/Vector.h>
#include <kxm/Zarch/Events/ZarchEvent.h>

namespace kxm {
namespace Zarch {

//! Acceleration event.
/*!
 *  \ingroup ZarchEvents
 */
class AccelerationEvent : public ZarchEvent {
  public:
    AccelerationEvent();
    AccelerationEvent(const Game::ActorName &anActor, bool anEnabled, const Vectoid::Vector &anAcceleration,
                      bool applyInLocalCoordSys);
    const EventType &Type() const { return type; }
    void Serialize(Core::Buffer *targetBuffer) const;
    void Deserialize(Core::Buffer::Reader *bufferReader);
    void Dispatch(EventHandlerCore *handler) const;
    
    static const EventType type;
    
    Game::ActorName    actor;
    Vectoid::Vector    acceleration;
    struct {
        bool           enabled;
        bool           applyInLocalCoordSys;
    }                  flags;
};

}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_ACCELERATIONEVENT_H_

