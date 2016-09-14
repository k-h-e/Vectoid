#include <Zarch/Events/PhysicsOverrideEvent.h>
#include <Zarch/EventHandlerCore.h>

using namespace kxm::Game;
using namespace kxm::Vectoid;

namespace kxm {
namespace Zarch {

PhysicsOverrideEvent::PhysicsOverrideEvent() {
    flags.overridePosition    = false;
    flags.overrideOrientation = true;
}

PhysicsOverrideEvent::PhysicsOverrideEvent(const ActorName &anActor, const Transform &aTransform)
        : actor(anActor),
          transform(aTransform) {
    flags.overridePosition    = false;
    flags.overrideOrientation = true;
}

const Game::Event::EventType PhysicsOverrideEvent::type("PhysicsOverrideEvent");

void PhysicsOverrideEvent::Serialize(Core::Buffer *targetBuffer) const {
    targetBuffer->Append(&actor, sizeof(actor));
    targetBuffer->Append(&transform, sizeof(transform));
    targetBuffer->Append(&flags, sizeof(flags));
}

void PhysicsOverrideEvent::Deserialize(Core::Buffer::Reader *bufferReader) {
    bufferReader->ReadBlock(&actor, sizeof(actor));
    bufferReader->ReadBlock(&transform, sizeof(transform));
    bufferReader->ReadBlock(&flags, sizeof(flags));
}

void PhysicsOverrideEvent::Dispatch(EventHandlerCore *handler) const {
    handler->Handle(*this);
}

}    // Namespace Zarch.
}    // Namespace kxm.
