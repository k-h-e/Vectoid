#ifndef KXM_ZARCH_PHYSICS_SAUCER_H_
#define KXM_ZARCH_PHYSICS_SAUCER_H_

#include <kxm/Zarch/Physics/Actor.h>

#include <kxm/Vectoid/BoundingBox.h>
#include <kxm/Vectoid/BoundingBoxCollisionChecker.h>
#include <kxm/Zarch/Physics/Body.h>

namespace kxm {
namespace Zarch {

class ActorCreationEvent;

namespace Physics {

class Data;

//! Represents an enemy saucer inside the physics sub system.
/*!
 *  \ingroup ZarchPhysics
 */
class Saucer : public Actor, public virtual Body::BodyUpdateHandlerInterface {
  public:
    Saucer(const std::shared_ptr<Data> &data);
    Saucer(const Saucer &other)            = delete;
    Saucer &operator=(const Saucer &other) = delete;
    Saucer(Saucer &&other)                 = delete;
    Saucer &operator=(Saucer &&other)      = delete;
    void GetTransform(Vectoid::Transform *outTransform) const;
    void GetVelocity(Vectoid::Vector *outVelocity);
    Vectoid::CollisionCheckerInterface *CollisionChecker();
    void Handle(const ActorCreationEvent &event);
    void Handle(const ControlsEvent &event);
    void ExecuteAction();
    
  private:
    void HandleBodyTransformUpdate(Vectoid::Transform *transform, bool *outVelocityUpdateRequired);
    void HandleBodyVelocityUpdate(Vectoid::Vector *velocity);
  
    Body                                 body_;
    Vectoid::BoundingBox                 boundingBox_;
    Vectoid::BoundingBoxCollisionChecker collisionChecker_;
};

}    // Namespace Physics.
}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_PHYSICS_SAUCER_H_