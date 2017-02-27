#include <kxm/Zarch/Physics/Lander.h>

#include <kxm/Core/NumberTools.h>
#include <kxm/Game/EventLoop.h>
#include <kxm/Zarch/MapParameters.h>
#include <kxm/Zarch/Terrain.h>
#include <kxm/Zarch/Events/ActorCreationEvent.h>
#include <kxm/Zarch/Events/ControlsEvent.h>
#include <kxm/Zarch/Events/MoveEvent.h>
#include <kxm/Zarch/Events/VelocityEvent.h>
#include <kxm/Zarch/Physics/Data.h>

using namespace std;
using namespace kxm::Core;
using namespace kxm::Vectoid;
using namespace kxm::Game;

namespace kxm {
namespace Zarch {
namespace Physics {

Lander::Lander()
        :  body_(this),
           axis1_(0.0f),
           axis2_(0.0f),
           thrusterActive_(false),
           oldThrusterActive_(false),
           heading_(0.0f, 0.0f, -1.0f),
           killVelocity_(false) {
    // Nop.
}

void Lander::GetTransform(Vectoid::Transform *outTransform) const {
    body_.GetTransform(outTransform);
}

void Lander::GetVelocity(Vectoid::Vector *outVelocity) {
    body_.GetVelocity(outVelocity);
}

CollisionCheckerInterface *Lander::CollisionChecker() {
    return &collisionChecker_;
}

void Lander::Handle(const ActorCreationEvent &event) {
    Actor::Reset(event);
    axis1_             = 0.0f;
    axis2_             = 0.0f;
    thrusterActive_    = false;
    oldThrusterActive_ = false;
    heading_        = Vector(0.0f, 0.0f, -1.0f);
    body_.SetTransform(event.initialTransform);
    body_.SetVelocity(event.initialVelocity);
    body_.EnableGravity(data_->mapParameters->gravity);
    body_.DisableAcceleration();
}

void Lander::Handle(const ControlsEvent &event) {
    Control control;
    for (int i = 0; i < event.Count(); ++i) {
        event.GetControl(i, &control);
        switch (control.Type()) {
            case Axis1Control:
                axis1_ = control.Argument();
                break;
            case Axis2Control:
                axis2_ = control.Argument();
                break;
            case ThrusterControl:
                thrusterActive_ = (control.Argument() > .5f);
                break;
            default:
                break;
        }
    }
    
    NumberTools::Clamp(&axis1_, -1.0f, 1.0f);
    float xAngle = (float)asin(axis1_) * 180.0f / NumberTools::piAsFloat;
    NumberTools::Clamp(&axis2_, -1.0f, 1.0f);
    float yAngle = -(float)asin(axis2_) * 180.0f / NumberTools::piAsFloat;
    float maxAngle = 30.0f;
    NumberTools::Clamp(&xAngle, -maxAngle, maxAngle);
    NumberTools::Clamp(&yAngle, -maxAngle, maxAngle);
    Vector speed(xAngle / maxAngle, 0.0f, yAngle / maxAngle);
    float  speedLength = speed.Length();
    if (speedLength > 0.0f) {
        heading_ = (1.0f/speedLength) * speed;
    }
    NumberTools::Clamp(&speedLength, 0.0f, 1.0f);
    
    Vector up(0.0f, 1.0f, 0.0f);
    Transform newLanderTransform(CrossProduct(up, -heading_), up, -heading_);
    newLanderTransform.Prepend(Transform(XAxis, -speedLength * 120.0f));
    newLanderTransform.Prepend(Transform(YAxis, 180.0));
    body_.SetOrientation(newLanderTransform);
    
    if (thrusterActive_ != oldThrusterActive_) {
        if (thrusterActive_) {
            body_.EnableAcceleration(data_->mapParameters->landerThrust * Vector(0.0f, 1.0f, 0.0f), true);
        }
        else {
            body_.DisableAcceleration();
        }
        oldThrusterActive_ = thrusterActive_;
    }
}

void Lander::ExecuteAction() {
    body_.UpdateForTimeStep(data_->updateDeltaTimeS);
}

void Lander::HandleBodyTransformUpdate(Transform *transform, bool *outVelocityUpdateRequired) {
    Data &data = *data_;
    
    Vector position;
    transform->GetTranslationPart(&position);
    data.mapParameters->xRange.ClampModulo(&position.x);
    data.mapParameters->zRange.ClampModulo(&position.z);
    float terrainHeight = data.terrain->Height(position.x, position.z);
    if (position.y < terrainHeight) {
        position.y                 = terrainHeight;
        killVelocity_              = true;
        *outVelocityUpdateRequired = true;
    }
    else {
        *outVelocityUpdateRequired = false;
    }
    transform->SetTranslationPart(position);

    data.eventLoop->Post(MoveEvent(name_, *transform));
}

void Lander::HandleBodyVelocityUpdate(Vector *velocity) {
    if (killVelocity_) {
        velocity->y   = 0.0f;
        killVelocity_ = false;
    }
    data_->eventLoop->Post(VelocityEvent(name_, *velocity));
}

}    // Namespace Physics.
}    // Namespace Zarch.
}    // Namespace kxm.
