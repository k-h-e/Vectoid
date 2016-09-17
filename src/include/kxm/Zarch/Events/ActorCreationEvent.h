#ifndef KXM_ZARCH_ACTORCREATIONEVENT_H_
#define KXM_ZARCH_ACTORCREATIONEVENT_H_

#include <kxm/Game/ActorName.h>
#include <kxm/Vectoid/Transform.h>
#include <kxm/Zarch/ActorType.h>
#include <kxm/Zarch/Events/ZarchEvent.h>

namespace kxm {
namespace Zarch {

//! Actor creation event.
/*!
 *  \ingroup ZarchEvents
 */
class ActorCreationEvent : public ZarchEvent {
  public:
    ActorCreationEvent();
    ActorCreationEvent(const Game::ActorName &anActor, ActorType anActorType,
                       const Vectoid::Transform &anInitialTransform, const Vectoid::Vector &anInitialVelocity,
                       const Game::ActorName &aLaunchingActor);
    const EventType &Type() const { return type; }
    void Dispatch(EventHandlerCore *handler) const;
    void Serialize(Core::Buffer *targetBuffer) const;
    void Deserialize(Core::Buffer::Reader *bufferReader);
    
    static const EventType type;
    
    Game::ActorName    actor;
    ActorType          actorType;
    Vectoid::Transform initialTransform;
    Vectoid::Vector    initialVelocity;
    Game::ActorName    launchingActor;
};
        
}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_ACTORCREATIONEVENT_H_
