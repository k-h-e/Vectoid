#include <kxm/Zarch/Physics/Shot.h>

#include <kxm/Game/EventLoop.h>
#include <kxm/Zarch/MapParameters.h>
#include <kxm/Zarch/Events/ActorCreationEvent.h>
#include <kxm/Zarch/Events/MoveEvent.h>
#include <kxm/Zarch/Physics/Data.h>

using namespace std;
using namespace kxm::Vectoid;
using namespace kxm::Game;

namespace kxm {
namespace Zarch {
namespace Physics {

Shot::Shot() {
    // Nop.
}

void Shot::Handle(const ActorCreationEvent &event) {
    name_      = event.actor;
    transform_ = event.initialTransform;
    velocity_  = event.initialVelocity;
}

void Shot::ExecuteAction() {
    velocity_.y += data_->updateDeltaTimeS * -data_->mapParameters->gravity;
    
    Vector position;
    transform_.GetTranslationPart(&position);
    position += data_->updateDeltaTimeS * velocity_;
    data_->mapParameters->xRange.ClampModulo(&position.x);
    data_->mapParameters->zRange.ClampModulo(&position.z);
    transform_.SetTranslationPart(position);
    data_->eventLoop->Post(MoveEvent(name_, position));
}

}    // Namespace Physics.
}    // Namespace Zarch.
}    // Namespace kxm.
