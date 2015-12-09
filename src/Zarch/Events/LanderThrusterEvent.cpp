//
//  LanderThrusterEvent.cpp
//  kxm
//
//  Created by Kai Hergenröther on 11/10/14.
//
//


#include <Zarch/Events/LanderThrusterEvent.h>
#include <Zarch/EventHandlerCore.h>


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

void LanderThrusterEvent::Dispatch(EventHandlerCore *handler) const {
    handler->HandleLanderThrusterEvent(*this);
}

}    // Namespace Zarch.
}    // Namespace kxm.
