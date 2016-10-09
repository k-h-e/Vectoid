#include <kxm/Zarch/Events/ControlsRequestEvent.h>
#include <kxm/Zarch/EventHandlerCore.h>

using namespace kxm::Game;

namespace kxm {
namespace Zarch {

ControlsRequestEvent::ControlsRequestEvent() {
    // Nop.
}

ControlsRequestEvent::ControlsRequestEvent(const ActorName &name)
    : ControlsCoreEvent(name) {
}

const Game::Event::EventType ControlsRequestEvent::type("ControlsRequestEvent");


void ControlsRequestEvent::Dispatch(EventHandlerCore *handler) const {
    handler->Handle(*this);
}

}    // Namespace Zarch.
}    // Namespace kxm.
