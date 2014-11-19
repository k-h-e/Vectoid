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

LanderMoveEvent::LanderMoveEvent() {
    // Nop.
}

LanderMoveEvent::LanderMoveEvent(const Vectoid::Transform &newLanderTransform)
    : newLanderTransform_(newLanderTransform) {
}

const Game::Event::EventType LanderMoveEvent::type("LanderMoveEvent");

void LanderMoveEvent::Serialize(Core::Buffer *targetBuffer) const {
}

void LanderMoveEvent::Deserialize(Core::Buffer::Reader *bufferReader) {
}

}    // Namespace Zarch.
}    // Namespace kxm.
