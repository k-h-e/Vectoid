#include <Zarch/Physics/Lander.h>

#include <kxm/Core/NumberTools.h>
#include <Game/EventLoop.h>
#include <Zarch/MapParameters.h>
#include <Zarch/Terrain.h>
#include <Zarch/Events/MoveEvent.h>
#include <Zarch/Events/VelocityEvent.h>
#include <Zarch/Events/ThrusterEvent.h>
#include <Zarch/Events/PhysicsOverrideEvent.h>
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
    name_      = name;
    transform_ = Transform();
    velocity_  = Vector();
}

void Lander::Handle(const PhysicsOverrideEvent &event) {
    if (event.flags.overrideOrientation) {
        Vector position;
        transform_.GetTranslationPart(&position);
        transform_ = event.transform;
        transform_.SetTranslationPart(position);
    }
}

void Lander::ExecuteAction() {
    Data &data = *data_;
    
    // Apply gravity...
    velocity_.y += data.updateDeltaTimeS * -data.mapParameters->gravity;
    
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
