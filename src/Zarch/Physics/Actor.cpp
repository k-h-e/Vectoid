#include <kxm/Zarch/Physics/Actor.h>

#include <kxm/Zarch/Events/ActorCreationEvent.h>

using namespace std;
using namespace kxm::Vectoid;
using namespace kxm::Game;

namespace kxm {
namespace Zarch {
namespace Physics {

Actor::Actor(const std::shared_ptr<Data> &data)
    : data_(data) {
    // Nop.
}

void Actor::Reset(const ActorCreationEvent &event) {
    name_ = event.actor;
}

}    // Namespace Physics.
}    // Namespace Zarch.
}    // Namespace kxm.
