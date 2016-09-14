#ifndef KXM_ZARCH_PHYSICSOVERRIDEEVENT_H_
#define KXM_ZARCH_PHYSICSOVERRIDEEVENT_H_

#include <Game/ActorName.h>
#include <Vectoid/Transform.h>
#include <Zarch/Events/ZarchEvent.h>

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
    const EventType &Type() const { return type; }
    void Serialize(Core::Buffer *targetBuffer) const;
    void Deserialize(Core::Buffer::Reader *bufferReader);
    void Dispatch(EventHandlerCore *handler) const;
    
    static const EventType type;
    
    Game::ActorName    actor;
    Vectoid::Transform transform;
    struct {
        bool           overridePosition;
        bool           overrideOrientation;
    }                  flags;
};

}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_PHYSICSOVERRIDEEVENT_H_

