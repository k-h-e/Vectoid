#ifndef KXM_ZARCH_OLDCONTROLSEVENT_H_
#define KXM_ZARCH_OLDCONTROLSEVENT_H_

#include <kxm/Game/ActorName.h>
#include <kxm/Zarch/ControlsState.h>
#include <kxm/Zarch/Events/ZarchEvent.h>

namespace kxm {
namespace Zarch {

namespace Physics {
    class Physics;
}

//! Controls event.
/*!
 *  \ingroup ZarchEvents
 */
class OldControlsEvent : public ZarchEvent {
  public:
    OldControlsEvent();
    OldControlsEvent(const Game::ActorName &anActor, const ControlsState &controlsState);
    const EventType &Type() const { return type; }
    void Serialize(Core::Buffer *targetBuffer) const;
    void Deserialize(Core::Buffer::Reader *bufferReader);
    void Dispatch(EventHandlerCore *handler) const;
    
    static const EventType type;
    
    Game::ActorName actor;
    ControlsState   controlsState;
};

}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_OLDCONTROLSEVENT_H_

