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
           headingVector_(0.0f, 0.0f, -1.0f),
           heading_(360),
           pitch_(360),
           up_(0.0f, 1.0f, 0.0f),
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
    headingVector_     = Vector(0.0f, 0.0f, -1.0f);
    heading_.SetValue(0.0f);
    pitch_.SetValue(0.0f);
    up_ = Vector(0.0f, 1.0f, 0.0f);
    body_.SetTransform(event.initialTransform);
    body_.SetVelocity(event.initialVelocity);
    body_.EnableGravity(data_->mapParameters->gravity);
    body_.DisableAcceleration();
}

void Lander::Handle(const ControlsEvent &event) {
    Data &data = *data_;
    
    Control control;
    for (int i = 0; i < event.Count(); ++i) {
        event.GetControl(i, &control);
        switch (control.Type()) {
            case Axis1Control:
                axis1_ = control.Argument();
                NumberTools::Clamp(&axis1_, -1.0f, 1.0f);
                break;
            case Axis2Control:
                axis2_ = control.Argument();
                NumberTools::Clamp(&axis2_, -1.0f, 1.0f);
                break;
            case ThrusterControl:
                thrusterActive_ = (control.Argument() > .5f);
                break;
            default:
                break;
        }
    }
    
    /*
    // Accelerometer...
    float xAngle   =  (float)asin(axis1_) * 180.0f / NumberTools::piAsFloat;
    float yAngle   = -(float)asin(axis2_) * 180.0f / NumberTools::piAsFloat;
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
    */
    
    /*
    // Game pad...
    Transform transform;
    body_.GetTransform(&transform);
    transform.SetTranslationPart(Vector(0.0f, 0.0f, 0.0f));
    Transform yaw(YAxis, -axis1_ * 180.0f * data.updateDeltaTimeS);
    transform.Append(yaw);
    Transform pitch(XAxis, axis2_ * 180.0f * data.updateDeltaTimeS);
    transform.Prepend(pitch);
    body_.SetOrientation(transform);
    */
    
    // Game pad 2..
    FloatModN newHeading = heading_,
              newPitch   = pitch_;
    Vector direction(axis1_, 0.0f, axis2_);
    float turnSpeed = direction.Length();
    if (turnSpeed != 0.0f) {
        direction = (1.0f / turnSpeed) * direction;
        NumberTools::ClampMax(&turnSpeed, 1.0f);
        //turnSpeed *= turnSpeed;
        
        float angle = (float)acos(axis1_) * 180.0f / NumberTools::piAsFloat;
        if (axis2_ < 0.0f) {
            angle = 360.0f - angle;
        }
        newHeading.SetValue(angle);
        newHeading.Add(90.0f);
        
        newPitch.SetValue(turnSpeed * 100.0f);
    }
    else {
        newPitch.SetValue(0.0f);
    }
    
    float maxTurnAngle = 360.0f * data.updateDeltaTimeS;
    heading_.MoveTo(newHeading, maxTurnAngle);
    pitch_.MoveTo(newPitch, maxTurnAngle);
    
    Transform transform(YAxis, heading_.Value());
    transform.Prepend(Transform(XAxis, pitch_.Value()));
    body_.SetOrientation(transform);
    
    /*
    // Mouse...
    {
        std::printf("controls=(%f, %f)\n", axis1_, axis2_);
    
        Vector u(axis1_, 0.0f, axis2_);
        float length = u.Length();
        if (length > 0.0f) {
            u = (1.0f/length) * u;
            Vector v(-u.z, 0.0f, u.x);
            Transform transform(v, Vector(0.0f, 1.0f, 0.0f), -u),
                      inverseTransform(Transform::InitAsInverseRotation, transform);
            Transform rotation(XAxis, -length * data.updateDeltaTimeS * 10000.0f);
            rotation.Prepend(inverseTransform);
            rotation.Append(transform);
            rotation.ApplyTo(&up_);
            
            std::printf("up=(%f, %f, %f)\n", up_.x, up_.y, up_.z);
            
            u   = up_;
            u.y = 0.0f;
            float length = u.Length();
            if (length > 0.0f) {
                u = (1.0f/length) * u;
                v = Vector(-u.z, 0.0f, u.x);
                Transform orientation(v, up_, CrossProduct(v, up_));
                orientation.Prepend(Transform(YAxis, 180.0f));
                body_.SetOrientation(orientation);
            }
        }
    }
    */
    
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
