#include <kxm/Zarch/Events/AccelerationEvent.h>
#include <kxm/Zarch/EventHandlerCore.h>

using namespace kxm::Game;
using namespace kxm::Vectoid;

namespace kxm {
namespace Zarch {

AccelerationEvent::AccelerationEvent() {
    flags.enabled              = false;
    flags.applyInLocalCoordSys = true;
}

AccelerationEvent::AccelerationEvent(const Game::ActorName &anActor, bool anEnabled, const Vector &anAcceleration,
                                     bool applyInLocalCoordSys)
        : actor(anActor),
          acceleration(anAcceleration) {
    flags.enabled              = anEnabled;
    flags.applyInLocalCoordSys = applyInLocalCoordSys;
}

const Game::Event::EventType AccelerationEvent::type("AccelerationEvent");

void AccelerationEvent::Serialize(Core::Buffer *targetBuffer) const {
    targetBuffer->Append(&actor, sizeof(actor));
    targetBuffer->Append(&acceleration, sizeof(acceleration));
    targetBuffer->Append(&flags, sizeof(flags));
}

void AccelerationEvent::Deserialize(Core::Buffer::Reader *bufferReader) {
    bufferReader->ReadBlock(&actor, sizeof(actor));
    bufferReader->ReadBlock(&acceleration, sizeof(acceleration));
    bufferReader->ReadBlock(&flags, sizeof(flags));
}

void AccelerationEvent::Dispatch(EventHandlerCore *handler) const {
    handler->Handle(*this);
}

}    // Namespace Zarch.
}    // Namespace kxm.
