#include <Zarch/Events/FrameGeneratedEvent.h>
#include <Zarch/EventHandlerCore.h>

namespace kxm {
namespace Zarch {
    
const Game::Event::EventType FrameGeneratedEvent::type("FrameGeneratedEvent");

void FrameGeneratedEvent::Dispatch(EventHandlerCore *handler) const {
    handler->HandleFrameGeneratedEvent(*this);
}
    
}    // Namespace Zarch.
}    // Namespace kxm.
