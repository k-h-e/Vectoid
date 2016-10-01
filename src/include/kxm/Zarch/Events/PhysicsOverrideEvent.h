#ifndef KXM_ZARCH_PHYSICSOVERRIDEEVENT_H_
#define KXM_ZARCH_PHYSICSOVERRIDEEVENT_H_

#include <kxm/Game/ActorName.h>
#include <kxm/Vectoid/Transform.h>
#include <kxm/Zarch/Events/ZarchEvent.h>

namespace kxm {
namespace Zarch {

//! Physics override event.
/*!
 *  \ingroup ZarchEvents
 */
class PhysicsOverrideEvent : public ZarchEvent {
  public:
    PhysicsOverrideEvent();
    PhysicsOverrideEvent(const Game::ActorName &anActor, const Vectoid::Transform &aTransform);
    PhysicsOverrideEvent(const Game::ActorName &anActor, const Vectoid::Transform &aTransform,
                         const Vectoid::Vector &aVelocity);
    const EventType &Type() const { return type; }
    void Serialize(Core::Buffer *targetBuffer) const;
    void Deserialize(Core::Buffer::Reader *bufferReader);
    void Dispatch(EventHandlerCore *handler) const;
    
    static const EventType type;
    
    Game::ActorName    actor;
    Vectoid::Transform transform;
    Vectoid::Vector    velocity;
    struct {
        bool           overridePosition;
        bool           overrideOrientation;
        bool           overrideVelocity;
    }                  flags;
};

}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_PHYSICSOVERRIDEEVENT_H_

