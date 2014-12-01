//
//  FrameTimeEvent.cpp
//  kxm
//
//  Created by Kai Hergenröther on 10/29/14.
//
//


#include <kxm/Zarch/Events/FrameTimeEvent.h>

#include <kxm/Zarch/Video/Video.h>
#include <kxm/Zarch/Physics/Physics.h>


namespace kxm {
namespace Zarch {

FrameTimeEvent::FrameTimeEvent()
    : timeS(0.0f) {
}

FrameTimeEvent::FrameTimeEvent(float timeS)
    : timeS(timeS) {
}

const Game::Event::EventType FrameTimeEvent::type("FrameTimeEvent");

void FrameTimeEvent::Serialize(Core::Buffer *targetBuffer) const {
    targetBuffer->Append(&timeS, sizeof(timeS));
}

void FrameTimeEvent::Deserialize(Core::Buffer::Reader *bufferReader) {
    bufferReader->ReadBlock(&timeS, sizeof(timeS));
}

void FrameTimeEvent::DispatchToVideo(Video *video) const {
    video->HandleFrameTimeEvent(*this);
}

void FrameTimeEvent::DispatchToPhysics(Physics *physics) const {
    physics->HandleFrameTimeEvent(*this);
}

}    // Namespace Zarch.
}    // Namespace kxm.
