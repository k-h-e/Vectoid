#ifndef KXM_ZARCH_INITIALIZATIONEVENT_H_
#define KXM_ZARCH_INITIALIZATIONEVENT_H_

#include <kxm/Zarch/Events/ZarchEvent.h>

namespace kxm {
namespace Zarch {

//! Initialization event.
/*!
 *  \ingroup ZarchEvents
 */
class InitializationEvent : public ZarchEvent {
  public:
    const EventType &Type() const { return type; }
    
    void Dispatch(EventHandlerCore *handler) const;
    
    static const EventType type;
};
        
}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_INITIALIZATIONEVENT_H_
