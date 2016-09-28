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

Lander::Lander()
        :  body_(this),
           killVelocity_(false) {
    // Nop.
}

void Lander::GetTransform(Vectoid::Transform *outTransform) {
    body_.GetTransform(outTransform);
}

void Lander::GetVelocity(Vectoid::Vector *outVelocity) {
    body_.GetVelocity(outVelocity);
}

void Lander::Handle(const ActorCreationEvent &event) {
    Actor::Reset(event);
    body_.SetTransform(event.initialTransform);
    body_.SetVelocity(event.initialVelocity);
    body_.EnableGravity(data_->mapParameters->gravity);
    body_.DisableAcceleration();
}

void Lander::Handle(const PhysicsOverrideEvent &event) {
    if (event.flags.overrideOrientation) {
        body_.SetOrientation(event.transform);
    }
}

void Lander::Handle(const AccelerationEvent &event) {
    if (event.flags.enabled) {
        body_.EnableAcceleration(event.acceleration, event.flags.applyInLocalCoordSys);
    }
    else {
        body_.DisableAcceleration();
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
