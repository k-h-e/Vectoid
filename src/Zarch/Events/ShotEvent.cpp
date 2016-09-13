#include <Zarch/Events/ShotEvent.h>
#include <Zarch/EventHandlerCore.h>

using namespace kxm::Game;
using namespace kxm::Vectoid;

namespace kxm {
namespace Zarch {

ShotEvent::ShotEvent()
        : shotExpired(false) {
    // Nop.
}

ShotEvent::ShotEvent(const ActorName &anActor, const Vector &aShotPosition, const Vector &aShotVelocity,
                     bool aShotExpired)
        : actor(anActor),
          shotPosition(aShotPosition),
          shotVelocity(aShotVelocity),
          shotExpired(aShotExpired) {
    // Nop.
}

const Game::Event::EventType ShotEvent::type("ShotEvent");

void ShotEvent::Serialize(Core::Buffer *targetBuffer) const {
    targetBuffer->Append(&actor, sizeof(actor));
    targetBuffer->Append(&shotPosition, sizeof(shotPosition));
    targetBuffer->Append(&shotVelocity, sizeof(shotVelocity));
    targetBuffer->Append(&shotExpired, sizeof(shotExpired));
}

void ShotEvent::Deserialize(Core::Buffer::Reader *bufferReader) {
    bufferReader->ReadBlock(&actor, sizeof(actor));
    bufferReader->ReadBlock(&shotPosition, sizeof(shotPosition));
    bufferReader->ReadBlock(&shotVelocity, sizeof(shotVelocity));
    bufferReader->ReadBlock(&shotExpired, sizeof(shotExpired));
}

void ShotEvent::Dispatch(EventHandlerCore *handler) const {
    handler->Handle(*this);
}

}    // Namespace Zarch.
}    // Namespace kxm.
