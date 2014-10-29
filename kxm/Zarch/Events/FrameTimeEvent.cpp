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

const Game::Event::EventType FrameTimeEvent::type("FrameTimeEvent");

void FrameTimeEvent::Serialize(Core::Buffer *targetBuffer) {
}

void FrameTimeEvent::Deserialize(Core::Buffer::Reader *bufferReader) {
}

}    // Namespace Zarch.
}    // Namespace kxm.
