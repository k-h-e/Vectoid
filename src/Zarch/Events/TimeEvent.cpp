#include <kxm/Zarch/Events/TimeEvent.h>
#include <kxm/Zarch/EventHandlerCore.h>

using namespace kxm::Game;

namespace kxm {
namespace Zarch {

TimeEvent::TimeEvent() {
    // Nop.
}

TimeEvent::TimeEvent(float aDeltaTimeS)
        : deltaTimeS(aDeltaTimeS) {
    // Nop.
}

const Game::Event::EventType TimeEvent::type("TimeEvent");

void TimeEvent::Serialize(Core::Buffer *targetBuffer) const {
    targetBuffer->Append(&deltaTimeS, sizeof(deltaTimeS));            // Sufficiently POD.
}

void TimeEvent::Deserialize(Core::Buffer::Reader *bufferReader) {
    bufferReader->ReadBlock(&deltaTimeS, sizeof(deltaTimeS));         // Sufficiently POD.
}

void TimeEvent::Dispatch(EventHandlerCore *handler) const {
    handler->Handle(*this);
}

}    // Namespace Zarch.
}    // Namespace kxm.
