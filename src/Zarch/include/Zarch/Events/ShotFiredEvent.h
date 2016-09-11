#ifndef KXM_ZARCH_SHOTFIREDEVENT_H_
#define KXM_ZARCH_SHOTFIREDEVENT_H_

#include <Game/ActorName.h>
#include <Vectoid/Vector.h>
#include <Zarch/Events/ZarchEvent.h>

namespace kxm {
namespace Zarch {

//! Shot fired event.
/*!
 *  \ingroup ZarchEvents
 */
class ShotFiredEvent : public ZarchEvent {
  public:
    ShotFiredEvent();
    ShotFiredEvent(const Game::ActorName &anActor, const Vectoid::Vector &aShotStartPosition,
                   const Vectoid::Vector &aShotStartVelocity);
    const EventType &Type() const { return type; }
    void Serialize(Core::Buffer *targetBuffer) const;
    void Deserialize(Core::Buffer::Reader *bufferReader);
    void Dispatch(EventHandlerCore *handler) const;
    
    static const EventType type;
    
    Game::ActorName actor;
    Vectoid::Vector shotStartPosition,
                    shotStartVelocity;
};

}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_SHOTFIREDEVENT_H_

