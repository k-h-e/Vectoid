#ifndef KXM_ZARCH_FRAMEGENERATEDEVENT_H_
#define KXM_ZARCH_FRAMEGENERATEDEVENT_H_

#include <Zarch/Events/ZarchEvent.h>

namespace kxm {
namespace Zarch {

class FrameGeneratedEvent : public ZarchEvent {
  public:
    const EventType &Type() const { return type; }
    
    void Dispatch(EventHandlerCore *handler) const;
    
    static const EventType type;
};
    
}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_FRAMEGENERATEDEVENT_H_
