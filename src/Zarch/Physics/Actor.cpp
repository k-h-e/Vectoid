#include <kxm/Zarch/Physics/Actor.h>

#include <kxm/Zarch/Events/ActorCreationEvent.h>

using namespace std;
using namespace kxm::Vectoid;
using namespace kxm::Game;

namespace kxm {
namespace Zarch {
namespace Physics {

void Actor::SetData(const shared_ptr<Data> &data) {
    if (data.get() != data_.get()) {    // Performance optimization.
        data_ = data;
    }
}

void Actor::Reset(const ActorCreationEvent &event) {
    name_      = event.actor;
    transform_ = event.initialTransform;
    velocity_  = event.initialVelocity;
}

void Actor::GetTransform(Transform *outTransform) {
    *outTransform = transform_;
}

void Actor::GetVelocity(Vector *outVelocity) {
    *outVelocity = velocity_;
}

}    // Namespace Physics.
}    // Namespace Zarch.
}    // Namespace kxm.
