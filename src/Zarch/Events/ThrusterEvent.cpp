#include <Zarch/Events/ThrusterEvent.h>
#include <Zarch/EventHandlerCore.h>

using namespace kxm::Game;

namespace kxm {
namespace Zarch {

ThrusterEvent::ThrusterEvent()
    : thrusterActive(false) {
}

ThrusterEvent::ThrusterEvent(const ActorName &anActor, bool aThrusterActive)
    : actor(anActor),
      thrusterActive(aThrusterActive) {
}

const Game::Event::EventType ThrusterEvent::type("ThrusterEvent");

void ThrusterEvent::Serialize(Core::Buffer *targetBuffer) const {
    targetBuffer->Append(&actor, sizeof(actor));
    targetBuffer->Append(&thrusterActive, sizeof(thrusterActive));
}

void ThrusterEvent::Deserialize(Core::Buffer::Reader *bufferReader) {
    bufferReader->ReadBlock(&actor, sizeof(actor));
    bufferReader->ReadBlock(&thrusterActive, sizeof(thrusterActive));
}

void ThrusterEvent::Dispatch(EventHandlerCore *handler) const {
    handler->Handle(*this);
}

}    // Namespace Zarch.
}    // Namespace kxm.
