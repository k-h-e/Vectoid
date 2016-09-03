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
        ++incarnations_[id];
    }
    else {
        id = (int)incarnations_.size();
        incarnations_.push_back(0u);
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