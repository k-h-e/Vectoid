#ifndef KXM_ZARCH_PHYSICS_LANDER_H_
#define KXM_ZARCH_PHYSICS_LANDER_H_

#include <memory>
#include <kxm/Core/FloatModN.h>
#include <kxm/Vectoid/Vector.h>
#include <kxm/Vectoid/PointCollisionChecker.h>
#include <kxm/Zarch/Physics/Actor.h>
#include <kxm/Zarch/Physics/Body.h>

namespace kxm {
namespace Zarch {

class ActorCreationEvent;
class ControlsEvent;

namespace Physics {

class Data;

//! Represents a lander inside the physics sub system.
/*!
 *  \ingroup ZarchPhysics
 */
class Lander : public Actor, public virtual Body::BodyUpdateHandlerInterface {
  public:
    Lander();
    Lander(const Lander &other)            = delete;
    Lander &operator=(const Lander &other) = delete;
    Lander(Lander &&other)                 = delete;
    Lander &operator=(Lander &&other)      = delete;
    void GetTransform(Vectoid::Transform *outTransform) const;
    void GetVelocity(Vectoid::Vector *outVelocity);
    Vectoid::CollisionCheckerInterface *CollisionChecker();
    void Handle(const ActorCreationEvent &event);
    void Handle(const ControlsEvent &event);
    void ExecuteAction();
    
  private:
    void HandleBodyTransformUpdate(Vectoid::Transform *transform, bool *outVelocityUpdateRequired);
    void HandleBodyVelocityUpdate(Vectoid::Vector *velocity);
  
    Body                           body_;
    float                          axis1_,
                                   axis2_;
    Vectoid::Vector                mouseVector_;
    bool                           thrusterActive_,
                                   oldThrusterActive_;
    Vectoid::Vector                headingVector_;
    Core::FloatModN                heading_,
                                   pitch_;
    Vectoid::Vector                up_;
    bool                           killVelocity_;
    Vectoid::PointCollisionChecker collisionChecker_;
};

}    // Namespace Physics.
}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_PHYSICS_LANDER_H_
