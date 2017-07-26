#include <kxm/Zarch/Events/GroundCollisionEvent.h>
#include <kxm/Zarch/EventHandlerCore.h>

using namespace kxm::Vectoid;
using namespace kxm::Game;

namespace kxm {
namespace Zarch {

GroundCollisionEvent::GroundCollisionEvent() {
    // Nop.
}

GroundCollisionEvent::GroundCollisionEvent(const Game::ActorName &anActor, const Transform &aTransform,
                                           const Vector &aVelocity)
    : actor(anActor),
      transform(aTransform),
      velocity(aVelocity) {
}

const Game::Event::EventType GroundCollisionEvent::type("GroundCollisionEvent");

void GroundCollisionEvent::Serialize(Core::Buffer *targetBuffer) const {
    targetBuffer->Append(&actor, sizeof(actor));            // Sufficiently POD.
    targetBuffer->Append(&transform, sizeof(transform));    // Sufficiently POD.
    targetBuffer->Append(&velocity, sizeof(velocity));      // Sufficiently POD.
}

void GroundCollisionEvent::Deserialize(Core::Buffer::Reader *bufferReader) {
    bufferReader->ReadBlock(&actor, sizeof(actor));            // Sufficiently POD.
    bufferReader->ReadBlock(&transform, sizeof(transform));    // Sufficiently POD.
    bufferReader->ReadBlock(&velocity, sizeof(velocity));      // Sufficiently POD.
}

void GroundCollisionEvent::Dispatch(EventHandlerCore *handler) const {
    handler->Handle(*this);
}

}    // Namespace Zarch.
}    // Namespace kxm.
