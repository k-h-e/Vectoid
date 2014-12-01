//
//  LanderVelocityEvent.cpp
//  kxm
//
//  Created by Kai Hergenröther on 11/10/14.
//
//

#include <kxm/Zarch/Events/LanderVelocityEvent.h>

#include <kxm/Zarch/Video/Video.h>


namespace kxm {
namespace Zarch {

LanderVelocityEvent::LanderVelocityEvent() {
    // Nop.
}

LanderVelocityEvent::LanderVelocityEvent(const Vectoid::Vector &aVelocity)
    : velocity(aVelocity) {
}

const Game::Event::EventType LanderVelocityEvent::type("LanderVelocityEvent");

void LanderVelocityEvent::Serialize(Core::Buffer *targetBuffer) const {
    targetBuffer->Append(&velocity, sizeof(velocity));    // Sufficiently POD.
}

void LanderVelocityEvent::Deserialize(Core::Buffer::Reader *bufferReader) {
    bufferReader->ReadBlock(&velocity, sizeof(velocity));    // Sufficiently POD.
}

void LanderVelocityEvent::DispatchToVideo(Video *video) const {
    video->HandleLanderVelocityEvent(*this);
}

}    // Namespace Zarch.
}    // Namespace kxm.
