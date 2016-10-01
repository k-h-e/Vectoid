#include <kxm/Zarch/GameLogic/Actor.h>

#include <kxm/Zarch/Events/ActorCreationEvent.h>

using namespace std;
using namespace kxm::Game;

namespace kxm {
namespace Zarch {
namespace GameLogic {

void Actor::SetData(const shared_ptr<Data> &data) {
    if (data.get() != data_.get()) {    // Performance optimization.
        data_ = data;
    }
}

void Actor::Reset(const ActorCreationEvent &event) {
    name_ = event.actor;
}

}    // Namespace GameLogic.
}    // Namespace Zarch.
}    // Namespace kxm.
