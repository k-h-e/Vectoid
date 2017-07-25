#include <kxm/Zarch/GameLogic/Shot.h>

#include <kxm/Zarch/MapParameters.h>
#include <kxm/Zarch/GameLogic/Data.h>
#include <kxm/Zarch/Events/ActorCreationEvent.h>

using namespace std;
using namespace kxm::Game;

namespace kxm {
namespace Zarch {
namespace GameLogic {

Shot::Shot()
        : ageS_(0.0f) {
    // Nop.
}

void Shot::Handle(const ActorCreationEvent &event) {
    Actor::Reset(event);
    ageS_ = 0.0f;
}

void Shot::HandleCollision(Actor *other) {
    other->HandleCollision(this);
}

void Shot::HandleCollision(Lander *lander) {
    // Nop.
}

void Shot::HandleCollision(Saucer *saucer) {
    // Nop.
}

void Shot::HandleCollision(Shot *shot) {
    // Nop.
}

void Shot::HandleGroundCollision() {
    // Nop.
}

void Shot::ExecuteAction() {
    ageS_ += data_->deltaTimeS;
    if (ageS_ >= data_->mapParameters->maxShotParticleAge) {
        data_->ScheduleActorForTermination(name_);
    }
}

}    // Namespace GameLogic.
}    // Namespace Zarch.
}    // Namespace kxm.
