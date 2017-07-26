#ifndef KXM_ZARCH_GROUNDCOLLISIONEVENT_H_
#define KXM_ZARCH_GROUNDCOLLISIONEVENT_H_

#include <kxm/Vectoid/Transform.h>
#include <kxm/Game/ActorName.h>
#include <kxm/Zarch/Events/ZarchEvent.h>

namespace kxm {
namespace Zarch {

//! Informs about an actor colliding with the ground.
/*!
 *  \ingroup ZarchEvents
 */
class GroundCollisionEvent : public ZarchEvent {
  public:
    GroundCollisionEvent();
    GroundCollisionEvent(const Game::ActorName &anActor, const Vectoid::Transform &aTransform,
                         const Vectoid::Vector &aVelocity);
    const EventType &Type() const { return type; }
    void Serialize(Core::Buffer *targetBuffer) const;
    void Deserialize(Core::Buffer::Reader *bufferReader);
    void Dispatch(EventHandlerCore *handler) const;
    
    static const EventType type;
    
    Game::ActorName    actor;
    Vectoid::Transform transform;
    Vectoid::Vector    velocity;
};

}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_GROUNDCOLLISIONEVENT_H_
