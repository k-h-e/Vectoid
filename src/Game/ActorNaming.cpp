#include <Game/ActorNaming.h>

#include <cstdio>

using namespace std;

namespace kxm {
namespace Game {

ActorNaming::ActorNaming() {
    // Nop.
}

ActorId ActorNaming::Get() {
    int id;
    if (freeIds_.size()) {
        id = *freeIds_.begin();
        freeIds_.erase(id);
        do {
            ++incarnations_[id];
        } while (!incarnations_[id]);    // Can never hand out an id with incarnation number of 0.
    }
    else {
        id = (int)incarnations_.size();
        incarnations_.push_back(1u);
    }
    printf("handing out id (%d, %u)\n", id, (unsigned int)incarnations_[id]);
    return ActorId(id, incarnations_[id]);
}

void ActorNaming::Put(const ActorId &id) {
    if ((id.id >= 0) && (id.id < (int)incarnations_.size())) {
        freeIds_.insert(id.id);
    }
}

}    // Namespace Game.
}    // Namespace kxm.