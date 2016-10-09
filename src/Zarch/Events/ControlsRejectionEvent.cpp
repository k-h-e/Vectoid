#include <kxm/Zarch/Events/ControlsRejectionEvent.h>
#include <kxm/Zarch/EventHandlerCore.h>

using namespace kxm::Game;

namespace kxm {
namespace Zarch {

ControlsRejectionEvent::ControlsRejectionEvent() {
    // Nop.
}

ControlsRejectionEvent::ControlsRejectionEvent(const ActorName &name)
    : ControlsCoreEvent(name) {
}

const Game::Event::EventType ControlsRejectionEvent::type("ControlsRejectionEvent");


void ControlsRejectionEvent::Dispatch(EventHandlerCore *handler) const {
    handler->Handle(*this);
}

}    // Namespace Zarch.
}    // Namespace kxm.
