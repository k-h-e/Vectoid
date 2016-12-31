#ifndef KXM_ZARCH_PHYSICS_SHOT_H_
#define KXM_ZARCH_PHYSICS_SHOT_H_

#include <kxm/Zarch/Physics/Actor.h>

#include <memory>
#include <kxm/Vectoid/CollidablePoint.h>

namespace kxm {
namespace Zarch {

class ActorCreationEvent;

namespace Physics {

class Data;

//! Represents a shot inside the physics sub system.
/*!
 *  \ingroup ZarchPhysics
 */
class Shot : public Actor {
  public:
    Shot();
    Shot(const Shot &other)            = delete;
    Shot &operator=(const Shot &other) = delete;
    Shot(Shot &&other)                 = delete;
    Shot &operator=(Shot &&other)      = delete;
    void GetTransform(Vectoid::Transform *outTransform);
    void GetVelocity(Vectoid::Vector *outVelocity);
    Vectoid::CollidableInterface *Collidable();
    void Handle(const ActorCreationEvent &event);
    void ExecuteAction();
    
  private:
    Vectoid::Vector          position_,
                             velocity_;
    Vectoid::CollidablePoint collidable_;
};

}    // Namespace Physics.
}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_PHYSICS_SHOT_H_
