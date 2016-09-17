#include <kxm/Zarch/Events/ActorCreationEvent.h>
#include <kxm/Zarch/EventHandlerCore.h>

using namespace kxm::Core;
using namespace kxm::Game;
using namespace kxm::Vectoid;

namespace kxm {
namespace Zarch {
    
const Event::EventType ActorCreationEvent::type("ActorCreationEvent");

ActorCreationEvent::ActorCreationEvent()
        : actor(0, 0u),
          actorType(InvalidActor) {
    // Nop.
}

ActorCreationEvent::ActorCreationEvent(const ActorName &anActor, ActorType anActorType,
                                       const Transform &anInitialTransform, const Vector &anInitialVelocity,
                                       const ActorName &aLaunchingActor)
        : actor(anActor),
          actorType(anActorType),
          initialTransform(anInitialTransform),
          initialVelocity(anInitialVelocity),
          launchingActor(aLaunchingActor) {
    // Nop.
}


void ActorCreationEvent::Dispatch(EventHandlerCore *handler) const {
    handler->Handle(*this);
}

void ActorCreationEvent::Serialize(Buffer *targetBuffer) const {
    targetBuffer->Append(&actor, sizeof(actor));
    targetBuffer->Append(&actorType, sizeof(actorType));
    targetBuffer->Append(&initialTransform, sizeof(initialTransform));
    targetBuffer->Append(&initialVelocity, sizeof(initialVelocity));
    targetBuffer->Append(&launchingActor, sizeof(launchingActor));
}

void ActorCreationEvent::Deserialize(Buffer::Reader *bufferReader) {
    bufferReader->ReadBlock(&actor, sizeof(actor));
    bufferReader->ReadBlock(&actorType, sizeof(actorType));
    bufferReader->ReadBlock(&initialTransform, sizeof(initialTransform));
    bufferReader->ReadBlock(&initialVelocity, sizeof(initialVelocity));
    bufferReader->ReadBlock(&launchingActor, sizeof(launchingActor));
}
    
}    // Namespace Zarch.
}    // Namespace kxm.
