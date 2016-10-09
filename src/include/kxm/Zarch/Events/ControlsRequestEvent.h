#ifndef KXM_ZARCH_CONTROLSREQUESTEVENT_H_
#define KXM_ZARCH_CONTROLSREQUESTEVENT_H_

#include <kxm/Zarch/Events/ControlsCoreEvent.h>

namespace kxm {
namespace Zarch {

//! Requests the issuing of certain controls updates/events for a given actor.
/*!
 *  \ingroup ZarchEvents
 */
class ControlsRequestEvent : public ControlsCoreEvent {
  public:
    ControlsRequestEvent();
    ControlsRequestEvent(const Game::ActorName &actor);
    const EventType &Type() const { return type; }
    void Dispatch(EventHandlerCore *handler) const;
    
    static const EventType type;
};

}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_CONTROLSREQUESTEVENT_H_
