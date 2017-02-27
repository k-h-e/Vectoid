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

void Shot::GetTransform(Vectoid::Transform *outTransform) const {
    *outTransform = Transform(position_);
}

void Shot::GetVelocity(Vectoid::Vector *outVelocity) {
    *outVelocity = velocity_;
}

CollisionCheckerInterface *Shot::CollisionChecker() {
    return &collisionChecker_;
}

void Shot::Handle(const ActorCreationEvent &event) {
    Actor::Reset(event);
    event.initialTransform.GetTranslationPart(&position_);
    velocity_ = event.initialVelocity;
}

void Shot::ExecuteAction() {
    velocity_.y += data_->updateDeltaTimeS * -data_->mapParameters->gravity;
    
    position_ += data_->updateDeltaTimeS * velocity_;
    data_->mapParameters->xRange.ClampModulo(&position_.x);
    data_->mapParameters->zRange.ClampModulo(&position_.z);
    data_->eventLoop->Post(MoveEvent(name_, position_));
}

}    // Namespace Physics.
}    // Namespace Zarch.
}    // Namespace kxm.
