//
//  ControlsStateEvent.cpp
//  kxm
//
//  Created by Kai Hergenröther on 11/10/14.
//
//


#include <Zarch/Events/ControlsStateEvent.h>
#include <Zarch/EventHandlerCore.h>


namespace kxm {
namespace Zarch {

ControlsStateEvent::ControlsStateEvent() {
    // Nop.
}

ControlsStateEvent::ControlsStateEvent(const ControlsState &someControlsState)
    : controlsState(someControlsState) {
}

const Game::Event::EventType ControlsStateEvent::type("ControlsStateEvent");

void ControlsStateEvent::Serialize(Core::Buffer *targetBuffer) const {
    targetBuffer->Append(&controlsState, sizeof(controlsState));   // Sufficiently POD.
}

void ControlsStateEvent::Deserialize(Core::Buffer::Reader *bufferReader) {
    bufferReader->ReadBlock(&controlsState, sizeof(controlsState));   // Sufficiently POD.
}

void ControlsStateEvent::Dispatch(EventHandlerCore *handler) const {
    handler->Handle(*this);
}

}    // Namespace Zarch.
}    // Namespace kxm.
