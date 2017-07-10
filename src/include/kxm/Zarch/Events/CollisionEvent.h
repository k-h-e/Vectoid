#ifndef KXM_ZARCH_COLLISIONEVENT_H_
#define KXM_ZARCH_COLLISIONEVENT_H_

#include <kxm/Game/ActorName.h>
#include <kxm/Zarch/Events/ZarchEvent.h>

namespace kxm {
namespace Zarch {

//! Collision event, including the ids of the two involved actors.
/*!
 *  \ingroup ZarchEvents
 */
class CollisionEvent : public ZarchEvent {
  public:
    CollisionEvent();
    CollisionEvent(const Game::ActorName &anActor, const Game::ActorName &anotherActor);
    const EventType &Type() const { return type; }
    void Serialize(Core::Buffer *targetBuffer) const;
    void Deserialize(Core::Buffer::Reader *bufferReader);
    void Dispatch(EventHandlerCore *handler) const;
    
    static const EventType type;
    
    Game::ActorName actor,
                    otherActor;
};

}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_COLLISIONEVENT_H_
