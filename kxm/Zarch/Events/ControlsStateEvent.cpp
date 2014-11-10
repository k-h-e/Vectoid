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

const Game::Event::EventType ControlsStateEvent::type("ControlsStateEvent");

void ControlsStateEvent::Serialize(Core::Buffer *targetBuffer) {
}

void ControlsStateEvent::Deserialize(Core::Buffer::Reader *bufferReader) {
}

}    // Namespace Zarch.
}    // Namespace kxm.
