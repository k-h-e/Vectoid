#include <kxm/Zarch/Events/ActorTerminationEvent.h>
#include <kxm/Zarch/EventHandlerCore.h>

using namespace kxm::Core;
using namespace kxm::Game;

namespace kxm {
namespace Zarch {
    
const Event::EventType ActorTerminationEvent::type("ActorTerminationEvent");

ActorTerminationEvent::ActorTerminationEvent() {
    // Nop.
}

ActorTerminationEvent::ActorTerminationEvent(const ActorName &anActor)
        : actor(anActor) {
    // Nop.
}

void ActorTerminationEvent::Dispatch(EventHandlerCore *handler) const {
    handler->Handle(*this);
}

void ActorTerminationEvent::Serialize(Buffer *targetBuffer) const {
    targetBuffer->Append(&actor, sizeof(actor));
}

void ActorTerminationEvent::Deserialize(Buffer::Reader *bufferReader) {
    bufferReader->ReadBlock(&actor, sizeof(actor));
}
    
}    // Namespace Zarch.
}    // Namespace kxm.
