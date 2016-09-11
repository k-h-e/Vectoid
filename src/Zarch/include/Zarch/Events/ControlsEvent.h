#ifndef KXM_ZARCH_CONTROLSEVENT_H_
#define KXM_ZARCH_CONTROLSEVENT_H_

#include <Game/ActorName.h>
#include <Zarch/ControlsState.h>
#include <Zarch/Events/ZarchEvent.h>

namespace kxm {
namespace Zarch {

namespace Physics {
    class Physics;
}

//! Controls event.
/*!
 *  \ingroup ZarchEvents
 */
class ControlsEvent : public ZarchEvent {
  public:
    ControlsEvent();
    ControlsEvent(const Game::ActorName &anActor, const ControlsState &controlsState);
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

#endif    // KXM_ZARCH_CONTROLSEVENT_H_

