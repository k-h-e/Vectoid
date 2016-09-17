#include <kxm/Zarch/Physics/Lander.h>

#include <kxm/Core/NumberTools.h>
#include <kxm/Game/EventLoop.h>
#include <kxm/Zarch/MapParameters.h>
#include <kxm/Zarch/Terrain.h>
#include <kxm/Zarch/Events/ActorCreationEvent.h>
#include <kxm/Zarch/Events/MoveEvent.h>
#include <kxm/Zarch/Events/VelocityEvent.h>
#include <kxm/Zarch/Events/PhysicsOverrideEvent.h>
#include <kxm/Zarch/Events/AccelerationEvent.h>
#include <kxm/Zarch/Physics/Data.h>

using namespace std;
using namespace kxm::Core;
using namespace kxm::Vectoid;
using namespace kxm::Game;

namespace kxm {
namespace Zarch {
namespace Physics {

Lander::Lander() {
    // Nop.
}

void Lander::Handle(const ActorCreationEvent &event) {
    name_                             = event.actor;
    transform_                        = event.initialTransform;
    velocity_                         = event.initialVelocity;
    acceleration_                     = Vector();
    accelerationEnabled_              = false;
    applyAccelerationInLocalCoordSys_ = false;
}

void Lander::Handle(const PhysicsOverrideEvent &event) {
    if (event.flags.overrideOrientation) {
        Vector position;
        transform_.GetTranslationPart(&position);
        transform_ = event.transform;
        transform_.SetTranslationPart(position);
    }
}

void Lander::Handle(const AccelerationEvent &event) {
    acceleration_                     = event.acceleration;
    accelerationEnabled_              = event.flags.enabled;
    applyAccelerationInLocalCoordSys_ = event.flags.applyInLocalCoordSys;
}

void Lander::ExecuteAction() {
    Data &data = *data_;
    
    // Apply gravity...
    velocity_.y += data.updateDeltaTimeS * -data.mapParameters->gravity;
    
    // Apply acceleration...?
    if (accelerationEnabled_) {
        Vector acceleration = acceleration_;
        if (applyAccelerationInLocalCoordSys_) {
            Transform orientation = transform_;
            orientation.SetTranslationPart(Vector());
            orientation.ApplyTo(&acceleration);
        }
        velocity_ += data.updateDeltaTimeS * acceleration;
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
    transform_.SetTranslationPart(position);
    
    data.eventLoop->Post(MoveEvent(name_, transform_));
    data.eventLoop->Post(VelocityEvent(name_, velocity_));
}

}    // Namespace Physics.
}    // Namespace Zarch.
}    // Namespace kxm.
