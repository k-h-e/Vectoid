#include <kxm/Zarch/Events/OldControlsEvent.h>
#include <kxm/Zarch/EventHandlerCore.h>

using namespace kxm::Game;

namespace kxm {
namespace Zarch {

OldControlsEvent::OldControlsEvent() {
    // Nop.
}

OldControlsEvent::OldControlsEvent(const ActorName &anActor, const ControlsState &someControlsState)
    : actor(anActor),
      controlsState(someControlsState) {
}

const Game::Event::EventType OldControlsEvent::type("OldControlsEvent");

void OldControlsEvent::Serialize(Core::Buffer *targetBuffer) const {
    targetBuffer->Append(&actor, sizeof(actor));
    targetBuffer->Append(&controlsState, sizeof(controlsState));   // Sufficiently POD.
}

void OldControlsEvent::Deserialize(Core::Buffer::Reader *bufferReader) {
    bufferReader->ReadBlock(&actor, sizeof(actor));
    bufferReader->ReadBlock(&controlsState, sizeof(controlsState));   // Sufficiently POD.
}

void OldControlsEvent::Dispatch(EventHandlerCore *handler) const {
    handler->Handle(*this);
}

}    // Namespace Zarch.
}    // Namespace kxm.
