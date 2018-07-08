#include <kxm/Zarch/AI/Actor.h>

#include <kxm/Zarch/Events/ActorCreationEvent.h>

using namespace std;

namespace kxm {
namespace Zarch {
namespace AI {

Actor::Actor(const std::shared_ptr<Data> &data)
    : data_(data) {
    // Nop.
}

void Actor::Reset(const ActorCreationEvent &event) {
    name_ = event.actor;
}

}    // Namespace AI.
}    // Namespace Zarch.
}    // Namespace kxm.
