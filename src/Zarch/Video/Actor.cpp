#include <kxm/Zarch/Video/Actor.h>

#include <kxm/Zarch/Events/ActorCreationEvent.h>

using namespace std;
using namespace kxm::Game;
using namespace kxm::Vectoid;

namespace kxm {
namespace Zarch {
namespace Video {

void Actor::SetData(const shared_ptr<Data> &data) {
    if (data.get() != data_.get()) {    // Performance optimization.
        data_ = data;
    }
}

}    // Namespace Video.
}    // Namespace Zarch.
}    // Namespace kxm.
