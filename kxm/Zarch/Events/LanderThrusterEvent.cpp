//
//  LanderThrusterEvent.cpp
//  kxm
//
//  Created by Kai Hergenröther on 11/10/14.
//
//


#include <kxm/Zarch/Events/LanderThrusterEvent.h>

#include <kxm/Zarch/Video/Video.h>


namespace kxm {
namespace Zarch {

LanderThrusterEvent::LanderThrusterEvent()
    : thrusterEnabled(false) {
}

LanderThrusterEvent::LanderThrusterEvent(bool aThrusterEnabled)
    : thrusterEnabled(aThrusterEnabled) {
}

const Game::Event::EventType LanderThrusterEvent::type("LanderThrusterEvent");

void LanderThrusterEvent::Serialize(Core::Buffer *targetBuffer) const {
    targetBuffer->Append(&thrusterEnabled, sizeof(thrusterEnabled));
}

void LanderThrusterEvent::Deserialize(Core::Buffer::Reader *bufferReader) {
    bufferReader->ReadBlock(&thrusterEnabled, sizeof(thrusterEnabled));
}

void LanderThrusterEvent::DispatchToVideo(Video *video) const {
    video->HandleLanderThrusterEvent(*this);
}

}    // Namespace Zarch.
}    // Namespace kxm.
