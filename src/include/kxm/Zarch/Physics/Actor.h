#ifndef ZARCH_PHYSICS_ACTOR_H_
#define ZARCH_PHYSICS_ACTOR_H_

#include <memory.h>
#include <kxm/Core/ActionInterface.h>
#include <kxm/Game/ActorName.h>
#include <kxm/Vectoid/Transform.h>
#include <kxm/Zarch/EventHandlerCore.h>

namespace kxm {
namespace Zarch {
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
    void GetTransform(Vectoid::Transform *outTransform);
    void GetVelocity(Vectoid::Vector *outVelocity);
  
  protected:
    Game::ActorName       name_;
    Vectoid::Transform    transform_;
    Vectoid::Vector       velocity_;
    std::shared_ptr<Data> data_;

};

}    // Namespace Physics
}    // Namespace Zarch
}    // Namespace kxm

#endif    // ZARCH_PHYSICS_ACTOR_H_
