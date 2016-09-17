#ifndef KXM_ZARCH_FRAMEGENERATEDEVENT_H_
#define KXM_ZARCH_FRAMEGENERATEDEVENT_H_

#include <kxm/Zarch/Events/ZarchEvent.h>

namespace kxm {
namespace Zarch {

//! Frame generated event.
/*!
 *  \ingroup ZarchEvents
 */
class FrameGeneratedEvent : public ZarchEvent {
  public:
    const EventType &Type() const { return type; }
    
    void Dispatch(EventHandlerCore *handler) const;
    
    static const EventType type;
};
    
}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_FRAMEGENERATEDEVENT_H_
