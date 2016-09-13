#ifndef KXM_ZARCH_ACTORCREATIONEVENT_H_
#define KXM_ZARCH_ACTORCREATIONEVENT_H_

#include <Game/ActorName.h>
#include <Vectoid/Transform.h>
#include <Zarch/ActorType.h>
#include <Zarch/Events/ZarchEvent.h>

namespace kxm {
namespace Zarch {

//! Actor creation event.
/*!
 *  \ingroup ZarchEvents
 */
class ActorCreationEvent : public ZarchEvent {
  public:
    ActorCreationEvent();
    ActorCreationEvent(const Game::ActorName &anActor, ActorType anActorType);
    ActorCreationEvent(const Game::ActorName &anActor, ActorType anActorType,
                       const Vectoid::Transform &anInitialTransform, const Vectoid::Vector &anInitialVelocity);
    const EventType &Type() const { return type; }
    void Dispatch(EventHandlerCore *handler) const;
    void Serialize(Core::Buffer *targetBuffer) const;
    void Deserialize(Core::Buffer::Reader *bufferReader);
    
    static const EventType type;
    
    Game::ActorName    actor;
    ActorType          actorType;
    Vectoid::Transform initialTransform;
    Vectoid::Vector    initialVelocity;
};
        
}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_ACTORCREATIONEVENT_H_
