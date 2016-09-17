#include <kxm/Zarch/GameLogic/Shot.h>

#include <kxm/Zarch/MapParameters.h>
#include <kxm/Zarch/GameLogic/Data.h>

using namespace std;
using namespace kxm::Game;

namespace kxm {
namespace Zarch {
namespace GameLogic {

Shot::Shot()
        : ageS_(0.0f) {
    // Nop.
}

void Shot::Reset(const ActorName &name, const shared_ptr<Data> &data) {
    if (data.get() != data_.get()) {    // Performance optimization.
        data_ = data;
    }
    name_ = name;
    ageS_ = 0.0f;
}

void Shot::ExecuteAction() {
    ageS_ += data_->deltaTimeS;
    if (ageS_ >= data_->mapParameters->maxShotParticleAge) {
        data_->actorsToTerminate.push_back(name_);
    }
}

}    // Namespace GameLogic.
}    // Namespace Zarch.
}    // Namespace kxm.
