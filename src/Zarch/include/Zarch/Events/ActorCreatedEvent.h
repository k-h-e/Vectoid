#ifndef KXM_ZARCH_ACTORCREATEDEVENT_H_
#define KXM_ZARCH_ACTORCREATEDEVENT_H_

#include <Game/ActorId.h>
#include <Zarch/ActorType.h>
#include <Zarch/Events/ZarchEvent.h>

namespace kxm {
namespace Zarch {

//! Actor created event.
/*!
 *  \ingroup ZarchEvents
 */
class ActorCreatedEvent : public ZarchEvent {
  public:
    ActorCreatedEvent();
    ActorCreatedEvent(Game::ActorId anActor, ActorType anActorType);
    const EventType &Type() const { return type; }
    void Dispatch(EventHandlerCore *handler) const;
    void Serialize(Core::Buffer *targetBuffer) const;
    void Deserialize(Core::Buffer::Reader *bufferReader);
    
    static const EventType type;
    
    Game::ActorId actor;
    ActorType     actorType;
};
        
}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_ACTORCREATEDEVENT_H_
