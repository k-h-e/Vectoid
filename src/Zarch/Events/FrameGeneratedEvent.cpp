#include <kxm/Zarch/Events/FrameGeneratedEvent.h>
#include <kxm/Zarch/EventHandlerCore.h>

namespace kxm {
namespace Zarch {
    
const Game::Event::EventType FrameGeneratedEvent::type("FrameGeneratedEvent");

void FrameGeneratedEvent::Dispatch(EventHandlerCore *handler) const {
    handler->Handle(*this);
}
    
}    // Namespace Zarch.
}    // Namespace kxm.
