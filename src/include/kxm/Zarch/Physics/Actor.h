#ifndef KXM_ZARCH_PHYSICS_ACTOR_H_
#define KXM_ZARCH_PHYSICS_ACTOR_H_

#include <memory>
#include <kxm/Core/ActionInterface.h>
#include <kxm/Game/ActorName.h>
#include <kxm/Vectoid/Transform.h>
#include <kxm/Vectoid/CollidableInterface.h>
#include <kxm/Zarch/EventHandlerCore.h>

namespace kxm {
namespace Zarch {

class ActorCreationEvent;

namespace Physics {

class Data;

//! Base class to actors inside the physics subsystem.
/*!
 *  \ingroup ZarchPhysics
 */
class Actor : public EventHandlerCore, public virtual Core::ActionInterface,
              public virtual Vectoid::CollidableInterface {
  public:
    Actor(const std::shared_ptr<Data> &data);
    // Default copy and move ok.
    void Reset(const ActorCreationEvent &event);
    virtual void GetVelocity(Vectoid::Vector *outVelocity) = 0;
  
  protected:
    Game::ActorName       name_;
    std::shared_ptr<Data> data_;
};

}    // Namespace Physics
}    // Namespace Zarch
}    // Namespace kxm

#endif    // KXM_ZARCH_PHYSICS_ACTOR_H_