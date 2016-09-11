#include <Zarch/Events/ControlsEvent.h>
#include <Zarch/EventHandlerCore.h>

using namespace kxm::Game;

namespace kxm {
namespace Zarch {

ControlsEvent::ControlsEvent() {
    // Nop.
}

ControlsEvent::ControlsEvent(const ActorName &anActor, const ControlsState &someControlsState)
    : actor(anActor),
      controlsState(someControlsState) {
}

const Game::Event::EventType ControlsEvent::type("ControlsEvent");

void ControlsEvent::Serialize(Core::Buffer *targetBuffer) const {
    targetBuffer->Append(&actor, sizeof(actor));
    targetBuffer->Append(&controlsState, sizeof(controlsState));   // Sufficiently POD.
}

void ControlsEvent::Deserialize(Core::Buffer::Reader *bufferReader) {
    bufferReader->ReadBlock(&actor, sizeof(actor));
    bufferReader->ReadBlock(&controlsState, sizeof(controlsState));   // Sufficiently POD.
}

void ControlsEvent::Dispatch(EventHandlerCore *handler) const {
    handler->Handle(*this);
}

}    // Namespace Zarch.
}    // Namespace kxm.
