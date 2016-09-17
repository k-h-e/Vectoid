#include <kxm/Zarch/Events/VelocityEvent.h>
#include <kxm/Zarch/EventHandlerCore.h>

using namespace kxm::Game;

namespace kxm {
namespace Zarch {

VelocityEvent::VelocityEvent() {
    // Nop.
}

VelocityEvent::VelocityEvent(const ActorName &anActor, const Vectoid::Vector &aVelocity)
    : actor(anActor),
      velocity(aVelocity) {
}

const Game::Event::EventType VelocityEvent::type("VelocityEvent");

void VelocityEvent::Serialize(Core::Buffer *targetBuffer) const {
    targetBuffer->Append(&actor, sizeof(actor));
    targetBuffer->Append(&velocity, sizeof(velocity));    // Sufficiently POD.
}

void VelocityEvent::Deserialize(Core::Buffer::Reader *bufferReader) {
    bufferReader->ReadBlock(&actor, sizeof(actor));
    bufferReader->ReadBlock(&velocity, sizeof(velocity));    // Sufficiently POD.
}

void VelocityEvent::Dispatch(EventHandlerCore *handler) const {
    handler->Handle(*this);
}

}    // Namespace Zarch.
}    // Namespace kxm.
