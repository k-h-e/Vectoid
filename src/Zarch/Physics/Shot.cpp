#include <Zarch/Physics/Shot.h>

#include <Game/EventLoop.h>
#include <Zarch/MapParameters.h>
#include <Zarch/Events/ActorCreationEvent.h>
#include <Zarch/Events/MoveEvent.h>
#include <Zarch/Physics/Data.h>

namespace kxm {
namespace Zarch {
namespace Physics {

Shot::Shot()
        : age_s_(0.0f),
          active_(false) {
    // Nop.
}

void Shot::Reset(const std::shared_ptr<Data> &data) {
    if (data.get() != data_.get()) {    // Performance optimization.
        data_ = data;
    }
}

void Shot::Handle(const ActorCreationEvent &event) {
    name_     = event.actor;
    event.initialTransform.GetTranslationPart(&position_);
    velocity_ = event.initialVelocity;
    age_s_    = 0.0f;
    active_   = true;
}

void Shot::Handle(const ActorTerminationEvent &event) {
    // Nop.
}

void Shot::ExecuteAction() {
    if (active_) {
        age_s_ += data_->updateDeltaTimeS;
        if (age_s_ >= data_->mapParameters->maxShotParticleAge) {
            //data_->eventLoop->Post(ShotEvent(name_, position_, velocity_, true));
            active_ = false;
        }
        else {
            velocity_.y += data_->updateDeltaTimeS * -data_->mapParameters->gravity;
            position_   += data_->updateDeltaTimeS * velocity_;
            data_->mapParameters->xRange.ClampModulo(&position_.x);
            data_->mapParameters->zRange.ClampModulo(&position_.z);
            data_->eventLoop->Post(MoveEvent(name_, position_));
        }
    }
}

}    // Namespace Physics.
}    // Namespace Zarch.
}    // Namespace kxm.
