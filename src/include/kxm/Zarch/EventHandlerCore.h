#ifndef KXM_ZARCH_EVENTHANDLERCORE_H_
#define KXM_ZARCH_EVENTHANDLERCORE_H_

#include <kxm/Core/Interface.h>

namespace kxm {
namespace Zarch {

class InitializationEvent;
class TimeEvent;
class ActorCreationEvent;
class ActorTerminationEvent;
class MoveEvent;
class VelocityEvent;
class AccelerationEvent;
class CollisionEvent;
class GroundCollisionEvent;
class ControlsRequestEvent;
class ControlsEvent;
class ControlsRejectionEvent;
class PlayerStatsEvent;
class FrameGeneratedEvent;
class TriggerEvent;

//! Base class to Zarch event handlers.
/*!
 *  \ingroup Zarch
 */
class EventHandlerCore : public virtual Core::Interface {
  public:
    virtual void Handle(const InitializationEvent &event);
    virtual void Handle(const TimeEvent &event);
    virtual void Handle(const ActorCreationEvent &event);
    virtual void Handle(const ActorTerminationEvent &event);
    virtual void Handle(const MoveEvent &event);
    virtual void Handle(const VelocityEvent &event);
    virtual void Handle(const AccelerationEvent &event);
    virtual void Handle(const CollisionEvent &event);
    virtual void Handle(const GroundCollisionEvent &event);
    virtual void Handle(const ControlsRequestEvent &event);
    virtual void Handle(const ControlsEvent &event);
    virtual void Handle(const ControlsRejectionEvent &event);
    virtual void Handle(const PlayerStatsEvent &event);
    virtual void Handle(const FrameGeneratedEvent &event);
    virtual void Handle(const TriggerEvent &event);
};

}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_EVENTHANDLERCORE_H_