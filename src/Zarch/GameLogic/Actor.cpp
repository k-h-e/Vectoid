#include <kxm/Zarch/GameLogic/Actor.h>

#include <kxm/Zarch/Events/ActorCreationEvent.h>

using namespace std;
using namespace kxm::Game;

namespace kxm {
namespace Zarch {
namespace GameLogic {

Actor::Actor(const std::shared_ptr<Data> &data)
    : data_(data) {
    // Nop.
}

void Actor::Reset(const ActorCreationEvent &event) {
    name_ = event.actor;
}

}    // Namespace GameLogic.
}    // Namespace Zarch.
}    // Namespace kxm.
