#include <kxm/Zarch/Physics/Body.h>

using namespace kxm::Vectoid;

namespace kxm {
namespace Zarch {
namespace Physics {

Body::Body(BodyUpdateHandlerInterface *updateHandler)
        : accelerationEnabled_(false),
          applyAccelerationInLocalCoordSys_(false),
          updateHandler_(updateHandler) {
    // Nop.
}

void Body::SetTransform(const Transform &transform) {
    transform_ = transform;
}

void Body::SetOrientation(const Transform &transform) {
    Vector position;
    transform_.GetTranslationPart(&position);
    transform_ = transform;
    transform_.SetTranslationPart(position);
}

void Body::GetTransform(Transform *outTransform) {
    *outTransform = transform_;
}

void Body::SetVelocity(const Vector &velocity) {
    velocity_ = velocity;
}

void Body::GetVelocity(Vector *outVelocity) {
    *outVelocity = velocity_;
}

void Body::EnableAcceleration(const Vectoid::Vector &acceleration, bool applyInLocalCoordSys) {
    acceleration_                     = acceleration;
    applyAccelerationInLocalCoordSys_ = applyInLocalCoordSys;
    accelerationEnabled_              = true;
}

void Body::DisableAcceleration() {
    accelerationEnabled_ = false;
}

void Body::EnableGravity(float gravity) {
    gravity_        = gravity;
    gravityEnabled_ = true;
}

void Body::DisableGravity() {
    gravityEnabled_ = false;
}

void Body::UpdateForTimeStep(float time_s) {
    // Apply gravity...?
    if (gravityEnabled_) {
        velocity_.y -= time_s * gravity_;
    }
    
    // Apply acceleration...?
    if (accelerationEnabled_) {
        Vector acceleration = acceleration_;
        if (applyAccelerationInLocalCoordSys_) {
            Transform orientation = transform_;
            orientation.SetTranslationPart(Vector());
            orientation.ApplyTo(&acceleration);
        }
        velocity_ += time_s * acceleration;
    }
    
    // Apply velocity...
    Vector position;
    transform_.GetTranslationPart(&position);
    position += time_s * velocity_;
    transform_.SetTranslationPart(position);
    
    // Call handler...?
    if (updateHandler_) {
        bool velocityUpdateRequired = false;
        updateHandler_->HandleBodyTransformUpdate(&transform_, &velocityUpdateRequired);
        if (velocityUpdateRequired || gravityEnabled_ || accelerationEnabled_) {
            updateHandler_->HandleBodyVelocityUpdate(&velocity_);
        }
    }
}

}    // Namespace Physics.
}    // Namespace Zarch.
}    // Namespace kxm.
