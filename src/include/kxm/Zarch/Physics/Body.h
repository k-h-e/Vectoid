#ifndef KXM_ZARCH_PHYSICS_BODY_H_
#define KXM_ZARCH_PHYSICS_BODY_H_

#include <kxm/Core/Interface.h>
#include <kxm/Vectoid/Transform.h>

namespace kxm {
namespace Zarch {
namespace Physics {

//! Physical body.
/*!
 *  \ingroup ZarchPhysics
 */
class Body {
  public:
    //! Interface to body update handlers.
    class BodyUpdateHandlerInterface : public virtual Core::Interface {
      public:
        //! The handler may update the body's transform.
        virtual void HandleBodyTransformUpdate(Vectoid::Transform *transform, bool *outVelocityUpdateRequired) = 0;
        //! The handler may update the body's velocity.
        virtual void HandleBodyVelocityUpdate(Vectoid::Vector *velocity) = 0;
    };
  
    //! Pass <c>nullptr</c> to not register a body update handler.
    /*!
     *  Weak reference, no ownership is assumed.
     *
     *  The handler's methods exclusively get called from \ref UpdateForTimeStep().
     */
    Body(BodyUpdateHandlerInterface *updateHandler);
    Body(const Body &other)            = delete;
    Body &operator=(const Body &other) = delete;
    Body(Body &&other)                 = delete;
    Body &operator=(Body &&other)      = delete;
    //! Sets the body's transform (position and orientation information) as specified.
    void SetTransform(const Vectoid::Transform &transform);
    //! Sets the body's orientation from the specified transform's orientation part.
    void SetOrientation(const Vectoid::Transform &transform);
    //! Gets the body's transform (position and orientation information).
    void GetTransform(Vectoid::Transform *outTransform) const;
    //! Sets the body's velociy as specified.
    void SetVelocity(const Vectoid::Vector &velocity);
    //! Gets the body's velociy.
    void GetVelocity(Vectoid::Vector *outVelocity);
    //! Sets the body's acceleration as specified and enables it, if it is disabled.
    void EnableAcceleration(const Vectoid::Vector &acceleration, bool applyInLocalCoordSys);
    //! Disables the body's acceleration if it is enabled.
    void DisableAcceleration();
    //! Sets the body's rotation as specified and enables it, if it is disabled.
    void EnableRotation(Vectoid::Axis axis, float angularVelocity);
    //! Disables the body's rotation if it is enabled.
    void DisableRotation();
    //! Sets the body's gravity and enables it, if it is disabled.
    void EnableGravity(float gravity);
    //! Disables the body's gravity if it is enabled.
    void DisableGravity();
    //! Applies the configured pysical effects for the specified time step.
    void UpdateForTimeStep(float time_s);

  private:
    Vectoid::Transform         transform_;
    Vectoid::Vector            velocity_;
    Vectoid::Vector            acceleration_;
    bool                       accelerationEnabled_,
                               applyAccelerationInLocalCoordSys_;
    Vectoid::Axis              rotationAxis_;
    float                      rotationAngularVelocity_;
    bool                       rotationEnabled_;
    float                      gravity_;
    bool                       gravityEnabled_;
    BodyUpdateHandlerInterface *updateHandler_;
};

}    // Namespace Physics
}    // Namespace Zarch
}    // Namespace kxm

#endif    // KXM_ZARCH_PHYSICS_BODY_H_
