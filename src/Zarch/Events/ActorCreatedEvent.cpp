#include <Zarch/Events/ActorCreatedEvent.h>
#include <Zarch/EventHandlerCore.h>

namespace kxm {
namespace Zarch {
    
const Game::Event::EventType ActorCreatedEvent::type("ActorCreatedEvent");

ActorCreatedEvent::ActorCreatedEvent()
        : actor(0, 0u),
          actorType(InvalidActor) {
    // Nop.
}

ActorCreatedEvent::ActorCreatedEvent(Game::ActorId anActor, ActorType anActorType)
        : actor(anActor),
          actorType(anActorType) {
    // Nop.
}

void ActorCreatedEvent::Dispatch(EventHandlerCore *handler) const {
    handler->Handle(*this);
}

void ActorCreatedEvent::Serialize(Core::Buffer *targetBuffer) const {
    targetBuffer->Append(&actor, sizeof(actor));
    targetBuffer->Append(&actorType, sizeof(actorType));
}

void ActorCreatedEvent::Deserialize(Core::Buffer::Reader *bufferReader) {
    bufferReader->ReadBlock(&actor, sizeof(actor));
    bufferReader->ReadBlock(&actorType, sizeof(actorType));
}
    
}    // Namespace Zarch.
}    // Namespace kxm.
