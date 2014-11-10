//
//  LanderMoveEvent.cpp
//  kxm
//
//  Created by Kai Hergenröther on 11/10/14.
//
//


#include <kxm/Zarch/Events/LanderMoveEvent.h>


namespace kxm {
namespace Zarch {

const Game::Event::EventType LanderMoveEvent::type("LanderMoveEvent");

void LanderMoveEvent::Serialize(Core::Buffer *targetBuffer) {
}

void LanderMoveEvent::Deserialize(Core::Buffer::Reader *bufferReader) {
}

}    // Namespace Zarch.
}    // Namespace kxm.
