#include <kxm/Zarch/Events/PhysicsUpdatedEvent.h>
#include <kxm/Zarch/EventHandlerCore.h>

namespace kxm {
namespace Zarch {
    
const Game::Event::EventType PhysicsUpdatedEvent::type("PhysicsUpdatedEvent");

void PhysicsUpdatedEvent::Dispatch(EventHandlerCore *handler) const {
    handler->Handle(*this);
}
    
}    // Namespace Zarch.
}    // Namespace kxm.
