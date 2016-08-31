#include <Zarch/Events/InitializationEvent.h>
#include <Zarch/EventHandlerCore.h>

namespace kxm {
namespace Zarch {
    
const Game::Event::EventType InitializationEvent::type("InitializationEvent");

void InitializationEvent::Dispatch(EventHandlerCore *handler) const {
    handler->Handle(*this);
}
    
}    // Namespace Zarch.
}    // Namespace kxm.
