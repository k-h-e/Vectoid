#ifndef KXM_ZARCH_PLAYERSTATSEVENT_H_
#define KXM_ZARCH_PLAYERSTATSEVENT_H_

#include <kxm/Game/ActorName.h>
#include <kxm/Zarch/Events/ZarchEvent.h>

namespace kxm {
namespace Zarch {

//! Transports player stats.
/*!
 *  \ingroup ZarchEvents
 */
class PlayerStatsEvent : public ZarchEvent {
  public:
    PlayerStatsEvent();
    PlayerStatsEvent(const Game::ActorName &actor);
    const EventType &Type() const { return type; }
    void Serialize(Core::Buffer *targetBuffer) const;
    void Deserialize(Core::Buffer::Reader *bufferReader);
    void Dispatch(EventHandlerCore *handler) const;
    
    static const EventType type;
    
    Game::ActorName    actor;
};

}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_PLAYERSTATSEVENT_H_
