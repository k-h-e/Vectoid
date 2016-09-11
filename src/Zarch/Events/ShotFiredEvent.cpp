#include <Zarch/Events/ShotFiredEvent.h>
#include <Zarch/EventHandlerCore.h>

using namespace kxm::Game;
using namespace kxm::Vectoid;

namespace kxm {
namespace Zarch {

ShotFiredEvent::ShotFiredEvent() {
    // Nop.
}

ShotFiredEvent::ShotFiredEvent(const ActorName &anActor, const Vector &aShotStartPosition,
                               const Vector &aShotStartVelocity)
        : actor(anActor),
          shotStartPosition(aShotStartPosition),
          shotStartVelocity(aShotStartVelocity) {
    // Nop.
}

const Game::Event::EventType ShotFiredEvent::type("ShotFiredEvent");

void ShotFiredEvent::Serialize(Core::Buffer *targetBuffer) const {
    targetBuffer->Append(&actor, sizeof(actor));
    targetBuffer->Append(&shotStartPosition, sizeof(shotStartPosition));
    targetBuffer->Append(&shotStartVelocity, sizeof(shotStartVelocity));
}

void ShotFiredEvent::Deserialize(Core::Buffer::Reader *bufferReader) {
    bufferReader->ReadBlock(&actor, sizeof(actor));
    bufferReader->ReadBlock(&shotStartPosition, sizeof(shotStartPosition));
    bufferReader->ReadBlock(&shotStartVelocity, sizeof(shotStartVelocity));
}

void ShotFiredEvent::Dispatch(EventHandlerCore *handler) const {
    handler->Handle(*this);
}

}    // Namespace Zarch.
}    // Namespace kxm.
