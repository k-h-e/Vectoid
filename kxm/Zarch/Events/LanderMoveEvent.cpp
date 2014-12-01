//
//  LanderMoveEvent.cpp
//  kxm
//
//  Created by Kai Hergenröther on 11/10/14.
//
//


#include <kxm/Zarch/Events/LanderMoveEvent.h>

#include <kxm/Zarch/Video/Video.h>


namespace kxm {
namespace Zarch {

LanderMoveEvent::LanderMoveEvent() {
    // Nop.
}

LanderMoveEvent::LanderMoveEvent(const Vectoid::Transform &aNewLanderTransform)
    : newLanderTransform(aNewLanderTransform) {
}

const Game::Event::EventType LanderMoveEvent::type("LanderMoveEvent");

void LanderMoveEvent::Serialize(Core::Buffer *targetBuffer) const {
    targetBuffer->Append(&newLanderTransform, sizeof(newLanderTransform));    // Sufficiently POD.
}

void LanderMoveEvent::Deserialize(Core::Buffer::Reader *bufferReader) {
    bufferReader->ReadBlock(&newLanderTransform, sizeof(newLanderTransform)); // Sufficiently POD.
}

void LanderMoveEvent::DispatchToVideo(Video *video) const {
    video->HandleLanderMoveEvent(*this);
}

}    // Namespace Zarch.
}    // Namespace kxm.
