#include <kxm/Zarch/Physics/Saucer.h>

#include <kxm/Game/EventLoop.h>
#include <kxm/Zarch/MapParameters.h>
#include <kxm/Zarch/Terrain.h>
#include <kxm/Zarch/Events/ActorCreationEvent.h>
#include <kxm/Zarch/Events/ControlsEvent.h>
#include <kxm/Zarch/Events/MoveEvent.h>
#include <kxm/Zarch/Events/VelocityEvent.h>
#include <kxm/Zarch/Physics/Data.h>

using namespace kxm::Vectoid;

namespace kxm {
namespace Zarch {
namespace Physics {

Saucer::Saucer()
        : body_(this),
          collisionChecker_(testBoundingBox_) {
    // Nop.
}

void Saucer::GetTransform(Transform *outTransform) const {
    body_.GetTransform(outTransform);
}

void Saucer::GetVelocity(Vector *outVelocity) {
    body_.GetVelocity(outVelocity);
}

CollisionCheckerInterface *Saucer::CollisionChecker() {
    return &collisionChecker_;
}

void Saucer::Handle(const ActorCreationEvent &event) {
    Actor::Reset(event);
    body_.SetTransform(event.initialTransform);
    body_.SetVelocity(event.initialVelocity);
    body_.DisableGravity();
    body_.DisableAcceleration();
}

void Saucer::Handle(const ControlsEvent &event) {
    static const float maxTravelVelocity = .4f,
                       verticalVelocity  = .2f;
    
    Vector velocity;
    body_.GetVelocity(&velocity);
    
    float rotationSpeedFactor = 0.0f;
    Control control;
    for (int i = 0; i < event.Count(); ++i) {
        bool updateRotationSpeedFactor = false;
        event.GetControl(i, &control);
        switch (control.Type()) {
            case Axis1Control:
                velocity.x = control.Argument() * maxTravelVelocity;
                updateRotationSpeedFactor = true;
                break;
            case Axis2Control:
                velocity.z = control.Argument() * maxTravelVelocity;
                updateRotationSpeedFactor = true;
                break;
            case ThrusterControl:
                if (control.Argument() > 0.0f) {
                    velocity.y = verticalVelocity;
                }
                else if (control.Argument() < 0.0f) {
                    velocity.y = -verticalVelocity;
                }
                else {
                    velocity.y = 0.0f;
                }
                break;
            default:
                break;
        }
        
        if (updateRotationSpeedFactor) {
            float absArg = control.Argument();
            if (absArg < 0.0f) {
                absArg = -absArg;
            }
            if (absArg > rotationSpeedFactor) {
                rotationSpeedFactor = absArg;
            }
        }
    }
    
    body_.SetVelocity(velocity);
    body_.EnableRotation(YAxis, rotationSpeedFactor * 30.0f);
}

void Saucer::ExecuteAction() {
    body_.UpdateForTimeStep(data_->updateDeltaTimeS);
}

void Saucer::HandleBodyTransformUpdate(Vectoid::Transform *transform, bool *outVelocityUpdateRequired) {
    Data &data = *data_;
    
    Vector position;
    transform->GetTranslationPart(&position);
    data.mapParameters->xRange.ClampModulo(&position.x);
    data.mapParameters->zRange.ClampModulo(&position.z);
    transform->SetTranslationPart(position);

    data.eventLoop->Post(MoveEvent(name_, *transform));
    *outVelocityUpdateRequired = false;
}

void Saucer::HandleBodyVelocityUpdate(Vectoid::Vector *velocity) {
    data_->eventLoop->Post(VelocityEvent(name_, *velocity));
}

}    // Namespace Physics.
}    // Namespace Zarch.
}    // Namespace kxm.
