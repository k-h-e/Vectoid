#ifndef KXM_ZARCH_PHYSICS_LANDER_H_
#define KXM_ZARCH_PHYSICS_LANDER_H_

#include <memory>
#include <kxm/Zarch/Physics/Actor.h>

namespace kxm {
namespace Zarch {

class ActorCreationEvent;
class PhysicsOverrideEvent;
class AccelerationEvent;

namespace Physics {

class Data;

//! Represents a lander inside the physics sub system.
/*!
 *  \ingroup ZarchPhysics
 */
class Lander : public Actor {
  public:
    Lander();
    Lander(const Lander &other)            = delete;
    Lander &operator=(const Lander &other) = delete;
    Lander(Lander &&other)                 = delete;
    Lander &operator=(Lander &&other)      = delete;
    void Handle(const ActorCreationEvent &event);
    void Handle(const PhysicsOverrideEvent &event);
    void Handle(const AccelerationEvent &event);
    void ExecuteAction();
    
  private:
    Vectoid::Vector acceleration_;
    bool            accelerationEnabled_,
                    applyAccelerationInLocalCoordSys_;
};

}    // Namespace Physics.
}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_PHYSICS_LANDER_H_
