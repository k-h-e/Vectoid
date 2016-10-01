#include <kxm/Zarch/Events/PhysicsOverrideEvent.h>
#include <kxm/Zarch/EventHandlerCore.h>

using namespace kxm::Game;
using namespace kxm::Vectoid;

namespace kxm {
namespace Zarch {

PhysicsOverrideEvent::PhysicsOverrideEvent() {
    flags.overridePosition    = false;
    flags.overrideOrientation = false;
    flags.overrideVelocity    = false;
}

PhysicsOverrideEvent::PhysicsOverrideEvent(const ActorName &anActor, const Transform &aTransform)
        : actor(anActor),
          transform(aTransform) {
    flags.overridePosition    = false;
    flags.overrideOrientation = true;
    flags.overrideVelocity    = false;
}

PhysicsOverrideEvent::PhysicsOverrideEvent(const ActorName &anActor, const Transform &aTransform,
                                           const Vector &aVelocity)
        : actor(anActor),
          transform(aTransform),
          velocity(aVelocity) {
    flags.overridePosition    = false;
    flags.overrideOrientation = true;
    flags.overrideVelocity    = true;
}

const Game::Event::EventType PhysicsOverrideEvent::type("PhysicsOverrideEvent");

void PhysicsOverrideEvent::Serialize(Core::Buffer *targetBuffer) const {
    targetBuffer->Append(&actor, sizeof(actor));
    targetBuffer->Append(&transform, sizeof(transform));
    targetBuffer->Append(&velocity, sizeof(velocity));
    targetBuffer->Append(&flags, sizeof(flags));
}

void PhysicsOverrideEvent::Deserialize(Core::Buffer::Reader *bufferReader) {
    bufferReader->ReadBlock(&actor, sizeof(actor));
    bufferReader->ReadBlock(&transform, sizeof(transform));
    bufferReader->ReadBlock(&velocity, sizeof(velocity));
    bufferReader->ReadBlock(&flags, sizeof(flags));
}

void PhysicsOverrideEvent::Dispatch(EventHandlerCore *handler) const {
    handler->Handle(*this);
}

}    // Namespace Zarch.
}    // Namespace kxm.
