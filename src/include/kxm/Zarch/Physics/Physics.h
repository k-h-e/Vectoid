/*!
 * \ingroup Zarch
 *
 * \defgroup ZarchPhysics Physics
 * \brief Zarch's physics subsystem.
 */

#ifndef KXM_ZARCH_PHYSICS_PHYSICS_H_
#define KXM_ZARCH_PHYSICS_PHYSICS_H_

#include <memory>

#include <kxm/Vectoid/Transform.h>
#include <kxm/Game/ActorName.h>
#include <kxm/Game/ActorMap.h>
#include <kxm/Game/Actions.h>
#include <kxm/Game/ReusableActors.h>
#include <kxm/Vectoid/Collider.h>
#include <kxm/Zarch/ActorType.h>
#include <kxm/Zarch/Events/TriggerEvent.h>
#include <kxm/Zarch/EventHandlerCore.h>

namespace kxm {

namespace Game {
    template<class EventClass, class EventHandlerClass> class EventLoop;
}

namespace Zarch {

class ActorCreationEvent;
class ActorTerminationEvent;
class ControlsEvent;
class AccelerationEvent;
class TriggerEvent;

namespace Physics {

class Data;
class Actor;
class Lander;
class Shot;
class Saucer;

//! Physics subsystem for the <c>Zarch</c> game.
/*!
 *  \ingroup ZarchPhysics
 */
class Physics : public EventHandlerCore, public virtual Vectoid::Collider<Game::ActorName>::DelegateInterface {
  public:
    Physics(std::shared_ptr<Game::EventLoop<ZarchEvent, EventHandlerCore>> eventLoop,
            TriggerEvent::Trigger anInTrigger, TriggerEvent::Trigger anOutTrigger);
    Physics(const Physics &other) = delete;
    Physics &operator=(const Physics &other) = delete;
    ~Physics();
    void ModifyOtherTransform(Vectoid::Transform *inOutOtherTransform, const Vectoid::Transform &ourTransform);
    void HandleCollision(const Game::ActorName &id, const Game::ActorName &otherId);
    void Handle(const ActorCreationEvent &event);
    void Handle(const ActorTerminationEvent &event);
    void Handle(const ControlsEvent &event);
    void Handle(const AccelerationEvent &event);
    void Handle(const TriggerEvent &event);
    
  private:
    enum CollisionGroup {
        PlayerCollisionGroup = 0,
        ShotsCollisionGroup,
        EnemiesCollisionGroup,
        CollisionGroupCount
    };
    
    struct ActorInfo {
        ActorType  type;
        int        storageId,
                   collidableId;
        Actor      *actor;
        ActorInfo() : type(LanderActor), storageId(0), collidableId(0), actor(nullptr) {}
        ActorInfo(ActorType aType, int aStorageId, int aCollidableId, Actor *anActor)
            : type(aType),
              storageId(aStorageId),
              collidableId(aCollidableId),
              actor(anActor) {}
        // Default copy/move okay.
    };

    std::shared_ptr<Data>              data_;
    Game::ActorMap<ActorInfo>          actorMap_;
    std::shared_ptr<Game::Actions>     actions_;
    Vectoid::Collider<Game::ActorName> collider_;
    Game::ReusableActors<Lander, Data> landers_;
    Game::ReusableActors<Shot, Data>   shots_;
    Game::ReusableActors<Saucer, Data> saucers_;
    TriggerEvent::Trigger              inTrigger_,
                                       outTrigger_;
};

}    // Namespace Physics.
}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_PHYSICS_PHYSICS_H_
