#include <kxm/Zarch/Events/CollisionEvent.h>
#include <kxm/Zarch/EventHandlerCore.h>

using namespace kxm::Game;

namespace kxm {
namespace Zarch {

CollisionEvent::CollisionEvent() {
    // Nop.
}

CollisionEvent::CollisionEvent(const Game::ActorName &anActor, const Game::ActorName &anotherActor)
    : actor(anActor),
      otherActor(anotherActor) {
}

const Game::Event::EventType CollisionEvent::type("CollisionEvent");

void CollisionEvent::Serialize(Core::Buffer *targetBuffer) const {
    targetBuffer->Append(&actor, sizeof(actor));              // Sufficiently POD.
    targetBuffer->Append(&otherActor, sizeof(otherActor));    // Sufficiently POD.
}

void CollisionEvent::Deserialize(Core::Buffer::Reader *bufferReader) {
    bufferReader->ReadBlock(&actor, sizeof(actor));              // Sufficiently POD.
    bufferReader->ReadBlock(&otherActor, sizeof(otherActor));    // Sufficiently POD.
}

void CollisionEvent::Dispatch(EventHandlerCore *handler) const {
    handler->Handle(*this);
}

}    // Namespace Zarch.
}    // Namespace kxm.
