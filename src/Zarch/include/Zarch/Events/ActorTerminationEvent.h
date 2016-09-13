#ifndef KXM_ZARCH_ACTORTERMINATIONEVENT_H_
#define KXM_ZARCH_ACTORTERMINATIONEVENT_H_

#include <Game/ActorName.h>
#include <Zarch/Events/ZarchEvent.h>

namespace kxm {
namespace Zarch {

//! Actor termination event.
/*!
 *  \ingroup ZarchEvents
 */
class ActorTerminationEvent : public ZarchEvent {
  public:
    ActorTerminationEvent();
    ActorTerminationEvent(const Game::ActorName &anActor);
    const EventType &Type() const { return type; }
    void Dispatch(EventHandlerCore *handler) const;
    void Serialize(Core::Buffer *targetBuffer) const;
    void Deserialize(Core::Buffer::Reader *bufferReader);
    
    static const EventType type;
    
    Game::ActorName actor;
};
        
}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_ACTORTERMINATIONEVENT_H_
