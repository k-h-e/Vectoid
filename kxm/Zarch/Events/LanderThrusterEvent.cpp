//
//  LanderThrusterEvent.cpp
//  kxm
//
//  Created by Kai Hergenröther on 11/10/14.
//
//


#include <kxm/Zarch/Events/LanderThrusterEvent.h>


namespace kxm {
namespace Zarch {

const Game::Event::EventType LanderThrusterEvent::type("LanderThrusterEvent");

void LanderThrusterEvent::Serialize(Core::Buffer *targetBuffer) {
}

void LanderThrusterEvent::Deserialize(Core::Buffer::Reader *bufferReader) {
}

}    // Namespace Zarch.
}    // Namespace kxm.
