#include <kxm/Zarch/Events/TriggerEvent.h>
#include <kxm/Zarch/EventHandlerCore.h>

namespace kxm {
namespace Zarch {

TriggerEvent::TriggerEvent()
    : trigger(NoTrigger),
      deltaTime_s(0.0f) {
    // Nop.
}

TriggerEvent::TriggerEvent(Trigger aTrigger, float aDeltaTime_s)
    : trigger(aTrigger),
      deltaTime_s(aDeltaTime_s) {
}

const Game::Event::EventType TriggerEvent::type("TriggerEvent");

void TriggerEvent::Serialize(Core::Buffer *targetBuffer) const {
    targetBuffer->Append(&trigger, sizeof(trigger));
    targetBuffer->Append(&deltaTime_s, sizeof(deltaTime_s));
}

void TriggerEvent::Deserialize(Core::Buffer::Reader *bufferReader) {
    bufferReader->ReadBlock(&trigger, sizeof(trigger));
    bufferReader->ReadBlock(&deltaTime_s, sizeof(deltaTime_s));
}

void TriggerEvent::Dispatch(EventHandlerCore *handler) const {
    handler->Handle(*this);
}

}    // Namespace Zarch.
}    // Namespace kxm.
