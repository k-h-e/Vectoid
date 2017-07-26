#include <kxm/Zarch/GameLogic/Shot.h>

#include <kxm/Zarch/MapParameters.h>
#include <kxm/Zarch/GameLogic/Data.h>
#include <kxm/Zarch/GameLogic/Lander.h>
#include <kxm/Zarch/GameLogic/Saucer.h>
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
    lander->HandleCollision(this);
}

void Shot::HandleCollision(Saucer *saucer) {
    saucer->HandleCollision(this);
}

void Shot::HandleCollision(Shot *shot) {
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
