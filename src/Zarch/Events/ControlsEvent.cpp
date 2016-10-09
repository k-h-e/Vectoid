#include <kxm/Zarch/Events/ControlsEvent.h>
#include <kxm/Zarch/EventHandlerCore.h>

using namespace kxm::Game;

namespace kxm {
namespace Zarch {

ControlsEvent::ControlsEvent() {
    // Nop.
}

ControlsEvent::ControlsEvent(const ActorName &name)
    : ControlsCoreEvent(name) {
}

const Game::Event::EventType ControlsEvent::type("ControlsEvent");


void ControlsEvent::Dispatch(EventHandlerCore *handler) const {
    handler->Handle(*this);
}

}    // Namespace Zarch.
}    // Namespace kxm.
