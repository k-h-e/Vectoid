#ifndef KXM_ZARCH_MOVEEVENT_H_
#define KXM_ZARCH_MOVEEVENT_H_

#include <kxm/Vectoid/Transform.h>
#include <kxm/Game/ActorName.h>
#include <kxm/Zarch/Events/ZarchEvent.h>

namespace kxm {
namespace Zarch {

//! Move event, including new position and new orientation.
/*!
 *  \ingroup ZarchEvents
 */
class MoveEvent : public ZarchEvent {
  public:
    MoveEvent();
    MoveEvent(const Game::ActorName &actor, const Vectoid::Transform &aTransform);
    const EventType &Type() const { return type; }
    void Serialize(Core::Buffer *targetBuffer) const;
    void Deserialize(Core::Buffer::Reader *bufferReader);
    void Dispatch(EventHandlerCore *handler) const;
    
    static const EventType type;
    
    Game::ActorName    actor;
    Vectoid::Transform transform;
};

}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_MOVEEVENT_H_
