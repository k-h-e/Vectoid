//
//  LanderVelocityEvent.cpp
//  kxm
//
//  Created by Kai Hergenröther on 11/10/14.
//
//

#include <kxm/Zarch/Events/LanderVelocityEvent.h>


namespace kxm {
namespace Zarch {

const Game::Event::EventType LanderVelocityEvent::type("LanderVelocityEvent");

void LanderVelocityEvent::Serialize(Core::Buffer *targetBuffer) {
}

void LanderVelocityEvent::Deserialize(Core::Buffer::Reader *bufferReader) {
}

}    // Namespace Zarch.
}    // Namespace kxm.
