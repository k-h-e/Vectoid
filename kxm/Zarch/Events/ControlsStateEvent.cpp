//
//  ControlsStateEvent.cpp
//  kxm
//
//  Created by Kai Hergenröther on 11/10/14.
//
//


#include <kxm/Zarch/Events/ControlsStateEvent.h>


namespace kxm {
namespace Zarch {

ControlsStateEvent::ControlsStateEvent() {
    // Nop.
}

ControlsStateEvent::ControlsStateEvent(const ControlsState &controlsState)
    : controlsState_(controlsState) {
}

const Game::Event::EventType ControlsStateEvent::type("ControlsStateEvent");

void ControlsStateEvent::Serialize(Core::Buffer *targetBuffer) const {
}

void ControlsStateEvent::Deserialize(Core::Buffer::Reader *bufferReader) {
}

}    // Namespace Zarch.
}    // Namespace kxm.
