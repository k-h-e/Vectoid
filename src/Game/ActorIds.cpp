#include <Game/ActorIds.h>

#include <Game/ActorId.h>

namespace kxm {
namespace Game {

void ActorIds::Register(const ActorId &id) {
    if (id.incarnation && (id.id >= 0)) {
        while ((int)incarnations_.size() <= id.id) {
            incarnations_.push_back(0u);
        }
        incarnations_[id.id] = id.incarnation;
    }
}

void ActorIds::Unregister(const ActorId &id) {
    if (Valid(id)) {
        incarnations_[id.id] = 0u;
    }
}

bool ActorIds::Valid(const ActorId &id) {
    if (id.incarnation) {
        if ((id.id >= 0) && (id.id < (int)incarnations_.size())) {
            if (id.incarnation == incarnations_[id.id]) {
                return true;
            }
        }
    }
    return false;
}

}    // Namespace Game.
}    // Namespace kxm.