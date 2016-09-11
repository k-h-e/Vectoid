#ifndef KXM_ZARCH_EVENTHANDLERCORE_H_
#define KXM_ZARCH_EVENTHANDLERCORE_H_

#include <kxm/Core/Interface.h>

namespace kxm {
namespace Zarch {

class InitializationEvent;
class ActorCreatedEvent;
class MoveEvent;
class VelocityEvent;
class ThrusterEvent;
class ShotFiredEvent;
class ControlsEvent;
class FrameGeneratedEvent;
class UpdatePhysicsEvent;
class PhysicsUpdatedEvent;

//! Base class to Zarch event handlers.
/*!
 *  \ingroup Zarch
 */
class EventHandlerCore : public virtual Core::Interface {
  public:
    virtual void Handle(const InitializationEvent &event);
    virtual void Handle(const ActorCreatedEvent &event);
    virtual void Handle(const MoveEvent &event);
    virtual void Handle(const VelocityEvent &event);
    virtual void Handle(const ThrusterEvent &event);
    virtual void Handle(const ShotFiredEvent &event);
    virtual void Handle(const ControlsEvent &event);
    virtual void Handle(const FrameGeneratedEvent &event);
    virtual void Handle(const UpdatePhysicsEvent &event);
    virtual void Handle(const PhysicsUpdatedEvent &event);
    };

}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_EVENTHANDLERCORE_H_