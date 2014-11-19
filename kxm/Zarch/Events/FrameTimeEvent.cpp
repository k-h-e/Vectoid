//
//  FrameTimeEvent.cpp
//  kxm
//
//  Created by Kai Hergenröther on 10/29/14.
//
//


#include <kxm/Zarch/Events/FrameTimeEvent.h>


namespace kxm {
namespace Zarch {

FrameTimeEvent::FrameTimeEvent()
    : timeS_(0.0f) {
}

FrameTimeEvent::FrameTimeEvent(float timeS)
    : timeS_(timeS) {
}

const Game::Event::EventType FrameTimeEvent::type("FrameTimeEvent");

void FrameTimeEvent::Serialize(Core::Buffer *targetBuffer) const {
}

void FrameTimeEvent::Deserialize(Core::Buffer::Reader *bufferReader) {
}

}    // Namespace Zarch.
}    // Namespace kxm.
