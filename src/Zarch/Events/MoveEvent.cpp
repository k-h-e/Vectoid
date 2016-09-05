#include <Zarch/Events/MoveEvent.h>
#include <Zarch/EventHandlerCore.h>

using namespace kxm::Game;

namespace kxm {
namespace Zarch {

MoveEvent::MoveEvent() {
    // Nop.
}

MoveEvent::MoveEvent(const ActorName &name, const Vectoid::Transform &aTransform)
    : actor(name),
      transform(aTransform) {
}

const Game::Event::EventType MoveEvent::type("MoveEvent");

void MoveEvent::Serialize(Core::Buffer *targetBuffer) const {
    targetBuffer->Append(&actor, sizeof(actor));            // Sufficiently POD.
    targetBuffer->Append(&transform, sizeof(transform));    // Sufficiently POD.
}

void MoveEvent::Deserialize(Core::Buffer::Reader *bufferReader) {
    bufferReader->ReadBlock(&actor, sizeof(actor));         // Sufficiently POD.
    bufferReader->ReadBlock(&transform, sizeof(transform)); // Sufficiently POD.
}

void MoveEvent::Dispatch(EventHandlerCore *handler) const {
    handler->Handle(*this);
}

}    // Namespace Zarch.
}    // Namespace kxm.
