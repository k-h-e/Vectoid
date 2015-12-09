#ifndef KXM_ZARCH_EVENTHANDLERCORE_H_
#define KXM_ZARCH_EVENTHANDLERCORE_H_


#include <Game/EventHandlerInterface.h>


namespace kxm {
namespace Zarch {

class FrameTimeEvent;
class ControlsStateEvent;
class LanderMoveEvent;
class LanderVelocityEvent;
class LanderThrusterEvent;

//! Base class to Zarch event handlers.
/*!
 *  \ingroup Zarch
 */
class EventHandlerCore : public virtual Game::EventHandlerInterface {
  public:
    virtual void HandleFrameTimeEvent(const FrameTimeEvent &event);
    virtual void HandleControlsStateEvent(const ControlsStateEvent &event);
    virtual void HandleLanderMoveEvent(const LanderMoveEvent &event);
    virtual void HandleLanderVelocityEvent(const LanderVelocityEvent &event);
    virtual void HandleLanderThrusterEvent(const LanderThrusterEvent &event);
};

}    // Namespace Zarch.
}    // Namespace kxm.


#endif    // KXM_ZARCH_EVENTHANDLERCORE_H_