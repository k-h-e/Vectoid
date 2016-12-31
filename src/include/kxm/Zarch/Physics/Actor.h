#ifndef KXM_ZARCH_PHYSICS_ACTOR_H_
#define KXM_ZARCH_PHYSICS_ACTOR_H_

#include <memory>
#include <kxm/Core/ActionInterface.h>
#include <kxm/Game/ActorName.h>
#include <kxm/Vectoid/Transform.h>
#include <kxm/Zarch/EventHandlerCore.h>

namespace kxm {

namespace Vectoid {
    class CollidableInterface;
}

namespace Zarch {

class ActorCreationEvent;

namespace Physics {

class Data;

//! Base class to actors inside the physics sub system.
/*!
 *  \ingroup ZarchPhysics
 */
class Actor : public EventHandlerCore, public virtual Core::ActionInterface {
  public:
    // Default copy and move ok.
    void SetData(const std::shared_ptr<Data> &data);
    void Reset(const ActorCreationEvent &event);
    virtual void GetTransform(Vectoid::Transform *outTransform) = 0;
    virtual void GetVelocity(Vectoid::Vector *outVelocity) = 0;
    //! Returns a collidable representing the actor for collision checking purposes - will live as long as the actor
    //! itself.
    virtual Vectoid::CollidableInterface *Collidable() = 0;
  
  protected:
    Game::ActorName       name_;
    std::shared_ptr<Data> data_;
};

}    // Namespace Physics
}    // Namespace Zarch
}    // Namespace kxm

#endif    // KXM_ZARCH_PHYSICS_ACTOR_H_
