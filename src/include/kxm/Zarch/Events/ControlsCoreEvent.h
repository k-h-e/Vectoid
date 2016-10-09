#ifndef KXM_ZARCH_CONTROLSCOREEVENT_H_
#define KXM_ZARCH_CONTROLSCOREEVENT_H_

#include <kxm/Game/ActorName.h>
#include <kxm/Zarch/Control.h>
#include <kxm/Zarch/Events/ZarchEvent.h>

namespace kxm {
namespace Zarch {

//! Base class to controls events.
/*!
 *  \ingroup ZarchEvents
 */
class ControlsCoreEvent : public ZarchEvent {
  public:
    static const int controlsMaxCount = 4;
  
    ControlsCoreEvent();
    ControlsCoreEvent(const Game::ActorName &actor);
    //! Adds the specified control information to the event.
    void AddControl(const Control &control);
    //! Gets the control information for the specified index (0-based).
    void GetControl(int index, Control *outControl);
    //! Tells the number of controls contained in the event.
    int Count();
    void Serialize(Core::Buffer *targetBuffer) const;
    void Deserialize(Core::Buffer::Reader *bufferReader);
    
    Game::ActorName actor;
    struct {
       int          count;
       ControlType  types[controlsMaxCount];
       float        arguments[controlsMaxCount];
    }               data;
};

}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_CONTROLSCOREEVENT_H_
