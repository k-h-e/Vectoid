#include <kxm/Zarch/AI/Actor.h>

#include <kxm/Zarch/Events/ActorCreationEvent.h>

using namespace std;

namespace kxm {
namespace Zarch {
namespace AI {

void Actor::SetData(const shared_ptr<Data> &data) {
    if (data.get() != data_.get()) {    // Performance optimization.
        data_ = data;
    }
}

void Actor::Reset(const ActorCreationEvent &event) {
    name_ = event.actor;
}

}    // Namespace AI.
}    // Namespace Zarch.
}    // Namespace kxm.
