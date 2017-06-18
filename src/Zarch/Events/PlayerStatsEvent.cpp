#include <kxm/Zarch/Events/PlayerStatsEvent.h>

#include <kxm/Zarch/EventHandlerCore.h>

using namespace kxm::Game;

namespace kxm {
namespace Zarch {

PlayerStatsEvent::PlayerStatsEvent() {
    // Nop.
}

PlayerStatsEvent::PlayerStatsEvent(const ActorName &name)
    : actor(name) {
}

const Game::Event::EventType PlayerStatsEvent::type("PlayerStatsEvent");

void PlayerStatsEvent::Serialize(Core::Buffer *targetBuffer) const {
    targetBuffer->Append(&actor, sizeof(actor));            // Sufficiently POD.
}

void PlayerStatsEvent::Deserialize(Core::Buffer::Reader *bufferReader) {
    bufferReader->ReadBlock(&actor, sizeof(actor));         // Sufficiently POD.
}

void PlayerStatsEvent::Dispatch(EventHandlerCore *handler) const {
    handler->Handle(*this);
}

}    // Namespace Zarch.
}    // Namespace kxm.
