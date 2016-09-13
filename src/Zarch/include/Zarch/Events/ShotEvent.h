#ifndef KXM_ZARCH_SHOTEVENT_H_
#define KXM_ZARCH_SHOTEVENT_H_

#include <Game/ActorName.h>
#include <Vectoid/Vector.h>
#include <Zarch/Events/ZarchEvent.h>

namespace kxm {
namespace Zarch {

//! Shot event.
/*!
 *  \ingroup ZarchEvents
 */
class ShotEvent : public ZarchEvent {
  public:
    ShotEvent();
    ShotEvent(const Game::ActorName &anActor, const Vectoid::Vector &aShotPosition,
              const Vectoid::Vector &aShotVelocity, bool aShotExpired);
    const EventType &Type() const { return type; }
    void Serialize(Core::Buffer *targetBuffer) const;
    void Deserialize(Core::Buffer::Reader *bufferReader);
    void Dispatch(EventHandlerCore *handler) const;
    
    static const EventType type;
    
    Game::ActorName actor;
    Vectoid::Vector shotPosition,
                    shotVelocity;
    bool            shotExpired;
};

}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_SHOTEVENT_H_

