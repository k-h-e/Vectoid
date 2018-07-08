#include <kxm/Zarch/Video/Actor.h>

#include <kxm/Zarch/Events/ActorCreationEvent.h>

using namespace std;
using namespace kxm::Game;
using namespace kxm::Vectoid;

namespace kxm {
namespace Zarch {
namespace Video {

Actor::Actor(const std::shared_ptr<Data> &data)
        : data_(data) {
    // Nop.
}

}    // Namespace Video.
}    // Namespace Zarch.
}    // Namespace kxm.
