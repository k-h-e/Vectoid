#ifndef KXM_ZARCH_VELOCITYEVENT_H_
#define KXM_ZARCH_VELOCITYEVENT_H_

#include <kxm/Vectoid/Vector.h>
#include <kxm/Game/ActorName.h>
#include <kxm/Zarch/Events/ZarchEvent.h>

namespace kxm {
namespace Zarch {

//! Velocity event.
/*!
 *  \ingroup ZarchEvents
 */
class VelocityEvent : public ZarchEvent {
  public:
    VelocityEvent();
    VelocityEvent(const Game::ActorName &anActor, const Vectoid::Vector &velocity);
    const EventType &Type() const { return type; }
    void Serialize(Core::Buffer *targetBuffer) const;
    void Deserialize(Core::Buffer::Reader *bufferReader);
    void Dispatch(EventHandlerCore *handler) const;
    
    static const EventType type;
    
    Game::ActorName actor;
    Vectoid::Vector velocity;
};

}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_VELOCITYEVENT_H_

