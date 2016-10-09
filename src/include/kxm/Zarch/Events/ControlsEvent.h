#ifndef KXM_ZARCH_CONTROLSEVENT_H_
#define KXM_ZARCH_CONTROLSEVENT_H_

#include <kxm/Zarch/Events/ControlsCoreEvent.h>

namespace kxm {
namespace Zarch {

//! Holds certain controls updates/events for a given actor.
/*!
 *  \ingroup ZarchEvents
 */
class ControlsEvent : public ControlsCoreEvent {
  public:
    ControlsEvent();
    ControlsEvent(const Game::ActorName &actor);
    const EventType &Type() const { return type; }
    void Dispatch(EventHandlerCore *handler) const;
    
    static const EventType type;
};

}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_CONTROLSEVENT_H_
