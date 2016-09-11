#ifndef KXM_ZARCH_THRUSTEREVENT_H_
#define KXM_ZARCH_THRUSTEREVENT_H_

#include <Game/ActorName.h>
#include <Zarch/Events/ZarchEvent.h>

namespace kxm {
namespace Zarch {

//! Thruster event.
/*!
 *  \ingroup ZarchEvents
 */
class ThrusterEvent : public ZarchEvent {
  public:
    ThrusterEvent();
    ThrusterEvent(const Game::ActorName &anActor, bool aThrusterActive);
    const EventType &Type() const { return type; }
    void Serialize(Core::Buffer *targetBuffer) const;
    void Deserialize(Core::Buffer::Reader *bufferReader);
    void Dispatch(EventHandlerCore *handler) const;
    
    static const EventType type;
    
    Game::ActorName actor;
    bool            thrusterActive;
};

}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_THRUSTEREVENT_H_

