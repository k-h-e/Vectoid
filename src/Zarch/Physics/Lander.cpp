#include <Zarch/Physics/Lander.h>

#include <kxm/Core/NumberTools.h>
#include <Game/EventLoop.h>
#include <Zarch/MapParameters.h>
#include <Zarch/Terrain.h>
#include <Zarch/Events/MoveEvent.h>
#include <Zarch/Events/ControlsEvent.h>
#include <Zarch/Events/VelocityEvent.h>
#include <Zarch/Events/ThrusterEvent.h>
#include <Zarch/Events/ShotFiredEvent.h>
#include <Zarch/Physics/Data.h>

using namespace std;
using namespace kxm::Core;
using namespace kxm::Vectoid;
using namespace kxm::Game;

namespace kxm {
namespace Zarch {
namespace Physics {

Lander::Lander() {
    Reset(ActorName(), shared_ptr<Data>());
}

void Lander::Reset(const ActorName &name, const shared_ptr<Data> &data) {
    if (data.get() != data_.get()) {    // Performance optimization.
        data_ = data;
    }
    name_                       = name;
    transform_                  = Transform();
    velocity_                   = Vector();
    heading_                    = Vector(0.0f, 0.0f, -1.0f);
    
    controls_.orientation       = Vector(0.0f, 1.0f, 0.0f);
    controls_.thruster          = false;
    controls_.trigger           = false;
    oldThrusterActive_          = false;
    shotsParticleTimeCarryOver_ = 0.0f;
}

void Lander::Handle(const ControlsEvent &event) {
    controls_ = event.controlsState;
}

void Lander::ExecuteAction() {
    Data &data = *data_;
    
    Vector lastLanderPosition;
    transform_.GetTranslationPart(&lastLanderPosition);
    
    float projection = controls_.orientation.x;
    NumberTools::Clamp(&projection, -1.0f, 1.0f);
    float xAngle = (float)asin(projection) * 180.0f / NumberTools::piAsFloat;
    projection = controls_.orientation.y;
    NumberTools::Clamp(&projection, -1.0f, 1.0f);
    float yAngle = -(float)asin(projection) * 180.0f / NumberTools::piAsFloat;
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
    
    // Apply gravity...
    velocity_.y += data.updateDeltaTimeS * -data.mapParameters->gravity;
    // Apply thrust...?
    if (controls_.thruster) {
        Vector thrustDirection(0.0f, 1.0f, 0.0f);
        newLanderTransform.ApplyTo(&thrustDirection);
        velocity_ += (data.updateDeltaTimeS * data.mapParameters->landerThrust) * thrustDirection;
    }
    Vector position = transform_.TranslationPart();
    position += data.updateDeltaTimeS * velocity_;
    data.mapParameters->xRange.ClampModulo(&position.x);
    data.mapParameters->zRange.ClampModulo(&position.z);
    float terrainHeight = data.terrain->Height(position.x, position.z);
    if (position.y < terrainHeight) {
        position.y  = terrainHeight;
        velocity_.y = 0.0f;
    }
    newLanderTransform.SetTranslationPart(position);
    transform_ = newLanderTransform;
    
    // Generate lander events...
    data.eventLoop->Post(MoveEvent(name_, newLanderTransform));
    data.eventLoop->Post(VelocityEvent(name_, velocity_));
    if (controls_.thruster != oldThrusterActive_) {
        data.eventLoop->Post(ThrusterEvent(name_, controls_.thruster));
        oldThrusterActive_ = controls_.thruster;
    }
    
    // Fire shots...?
    if (controls_.trigger && (data_->updateDeltaTimeS > 0.0f)) {
        Vector landerPosition;
        transform_.GetTranslationPart(&landerPosition);
        Transform transform(transform_);
        transform.SetTranslationPart(Vector());
        float timeLeft = data_->updateDeltaTimeS - shotsParticleTimeCarryOver_;
        while (timeLeft > 0.0f) {
            Vector firingDirection(0.0f, 0.0f, 1.0f),
                   startPoint(0.0f, 0.0f, .55f);
            transform.ApplyTo(&firingDirection);
            transform.ApplyTo(&startPoint);
            Vector shotStartVelocity = velocity_ + data_->mapParameters->shotVelocity*firingDirection;
            float t = 1.0f - timeLeft/data_->updateDeltaTimeS;
            Vector shotStartPosition =   (1.0f - t)*lastLanderPosition + t*landerPosition
                                       + startPoint + timeLeft*shotStartVelocity;
            data.eventLoop->Post(ShotFiredEvent(name_, shotStartPosition, shotStartVelocity));
            timeLeft -= data_->mapParameters->shotFiringInterval;
        }
        shotsParticleTimeCarryOver_ = -timeLeft;
    }

}

}    // Namespace Physics.
}    // Namespace Zarch.
}    // Namespace kxm.
