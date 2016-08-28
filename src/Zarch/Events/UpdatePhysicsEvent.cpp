#include <Zarch/Events/UpdatePhysicsEvent.h>
#include <Zarch/EventHandlerCore.h>

namespace kxm {
namespace Zarch {
    
const Game::Event::EventType UpdatePhysicsEvent::type("UpdatePhysicsEvent");

void UpdatePhysicsEvent::Dispatch(EventHandlerCore *handler) const {
    handler->Handle(*this);
}
    
}    // Namespace Zarch.
}    // Namespace kxm.
