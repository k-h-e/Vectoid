#include <Zarch/GameLogic/Lander.h>

#include <cstdio>
#include <kxm/Core/NumberTools.h>
#include <Game/EventLoop.h>
#include <Game/ActorNaming.h>
#include <Vectoid/Transform.h>
#include <Zarch/MapParameters.h>
#include <Zarch/Events/ActorCreationEvent.h>
#include <Zarch/Events/ControlsEvent.h>
#include <Zarch/Events/PhysicsOverrideEvent.h>
#include <Zarch/Events/AccelerationEvent.h>
#include <Zarch/GameLogic/Data.h>

using namespace std;
using namespace kxm::Core;
using namespace kxm::Game;
using namespace kxm::Vectoid;

namespace kxm {
namespace Zarch {
namespace GameLogic {

Lander::Lander() {
    Reset(ActorName(), shared_ptr<Data>());
}

void Lander::Reset(const ActorName &name, const shared_ptr<Data> &data) {
    if (data.get() != data_.get()) {    // Performance optimization.
        data_ = data;
    }
    name_              = name;
    heading_           = Vector(0.0f, 0.0f, -1.0f);
    oldThrusterActive_ = false;
    trigger_           = false;
    triggerTimeS_      = 0.0f;
}

void Lander::Handle(const ControlsEvent &event) {
    const ControlsState &controls = event.controlsState;
    trigger_ = controls.trigger;
    
    float projection = controls.orientation.x;
    NumberTools::Clamp(&projection, -1.0f, 1.0f);
    float xAngle = (float)asin(projection) * 180.0f / NumberTools::piAsFloat;
    projection = controls.orientation.y;
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
    
    data_->eventLoop->Post(PhysicsOverrideEvent(name_, newLanderTransform));
    
    if (controls.thruster != oldThrusterActive_) {
        data_->eventLoop->Post(AccelerationEvent(name_, controls.thruster,
                                                 data_->mapParameters->landerThrust * Vector(0.0f, 1.0f, 0.0f), true));
        oldThrusterActive_ = controls.thruster;
    }
}

void Lander::ExecuteAction() {
    if (trigger_) {
        triggerTimeS_ += data_->deltaTimeS;
    }
    else {
        triggerTimeS_ = 0.0f;
    }
    
    if (triggerTimeS_ > 0.0f) {
        data_->actorCreationEvents.push_back(
            ActorCreationEvent(data_->actorNaming.Get(), ShotActor, Transform(Vector(0.0f, 0.0f, .55f)),
                               data_->mapParameters->shotVelocity * Vector(0.0f, 0.0f, 1.0f), name_));
        triggerTimeS_ -= data_->mapParameters->shotFiringInterval;
    }
}

}    // Namespace GameLogic.
}    // Namespace Zarch.
}    // Namespace kxm.
