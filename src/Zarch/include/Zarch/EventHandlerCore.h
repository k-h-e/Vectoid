#ifndef KXM_ZARCH_EVENTHANDLERCORE_H_
#define KXM_ZARCH_EVENTHANDLERCORE_H_

#include <kxm/Core/Interface.h>

namespace kxm {
namespace Zarch {

class FrameTimeEvent;
class FrameGeneratedEvent;
class UpdatePhysicsEvent;
class PhysicsUpdatedEvent;
class ControlsStateEvent;
class LanderMoveEvent;
class LanderVelocityEvent;
class LanderThrusterEvent;

//! Base class to Zarch event handlers.
/*!
 *  \ingroup Zarch
 */
class EventHandlerCore : public virtual Core::Interface {
  public:
    virtual void Handle(const FrameTimeEvent &event);
    virtual void Handle(const FrameGeneratedEvent &event);
    virtual void Handle(const UpdatePhysicsEvent &event);
    virtual void Handle(const PhysicsUpdatedEvent &event);
    virtual void Handle(const ControlsStateEvent &event);
    virtual void Handle(const LanderMoveEvent &event);
    virtual void Handle(const LanderVelocityEvent &event);
    virtual void Handle(const LanderThrusterEvent &event);
};

}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_EVENTHANDLERCORE_H_