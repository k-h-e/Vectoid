#include <kxm/Zarch/GameLogic/Saucer.h>

#include <kxm/Zarch/MapParameters.h>
#include <kxm/Zarch/GameLogic/Data.h>

using namespace std;
using namespace kxm::Game;

namespace kxm {
namespace Zarch {
namespace GameLogic {

Saucer::Saucer() {
    // Nop.
}

void Saucer::Handle(const ActorCreationEvent &event) {
    name_ = event.actor;
}

void Saucer::ExecuteAction() {

}

}    // Namespace GameLogic.
}    // Namespace Zarch.
}    // Namespace kxm.
