#include <kxm/Zarch/Events/ControlsCoreEvent.h>

#include <assert.h>

using namespace kxm::Game;

namespace kxm {
namespace Zarch {

ControlsCoreEvent::ControlsCoreEvent() {
    data.count = 0;
}

ControlsCoreEvent::ControlsCoreEvent(const ActorName &name)
    : actor(name) {
    data.count = 0;
}

void ControlsCoreEvent::AddControl(const Control &control) {
    assert(data.count < controlsMaxCount);
    data.types[data.count]     = control.Type();
    data.arguments[data.count] = control.Argument();
    ++data.count;
}

void ControlsCoreEvent::GetControl(int index, Control *outControl) {
    assert((index >= 0) && (index < controlsMaxCount));
    *outControl = Control(data.types[index], data.arguments[index]);
}

int ControlsCoreEvent::Count() {
    return data.count;
}

void ControlsCoreEvent::Serialize(Core::Buffer *targetBuffer) const {
    targetBuffer->Append(&actor, sizeof(actor));
    targetBuffer->Append(&data, sizeof(data));
}

void ControlsCoreEvent::Deserialize(Core::Buffer::Reader *bufferReader) {
    bufferReader->ReadBlock(&actor, sizeof(actor));
    bufferReader->ReadBlock(&data, sizeof(data));
}

}    // Namespace Zarch.
}    // Namespace kxm.
