#ifndef KXM_ZARCH_PHYSICSUPDATEDEVENT_H_
#define KXM_ZARCH_PHYSICSUPDATEDEVENT_H_

#include <Zarch/Events/ZarchEvent.h>

namespace kxm {
namespace Zarch {

//! Physics updated event.
/*!
 *  \ingroup ZarchEvents
 */
class PhysicsUpdatedEvent : public ZarchEvent {
public:
    const EventType &Type() const { return type; }
    
    void Dispatch(EventHandlerCore *handler) const;
    
    static const EventType type;
};
        
}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_PHYSICSUPDATEDEVENT_H_
