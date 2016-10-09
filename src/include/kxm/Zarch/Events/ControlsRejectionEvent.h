#ifndef KXM_ZARCH_CONTROLSREJECTIONEVENT_H_
#define KXM_ZARCH_CONTROLSREJECTIONEVENT_H_

#include <kxm/Zarch/Events/ControlsCoreEvent.h>

namespace kxm {
namespace Zarch {

//! Informs about that requests for certain controls updates/events for a given actor were rejected.
/*!
 *  \ingroup ZarchEvents
 */
class ControlsRejectionEvent : public ControlsCoreEvent {
  public:
    ControlsRejectionEvent();
    ControlsRejectionEvent(const Game::ActorName &actor);
    const EventType &Type() const { return type; }
    void Dispatch(EventHandlerCore *handler) const;
    
    static const EventType type;
};

}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_CONTROLSREJECTIONEVENT_H_
