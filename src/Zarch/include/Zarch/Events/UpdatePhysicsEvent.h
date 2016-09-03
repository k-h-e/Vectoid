#ifndef KXM_ZARCH_UPDATEPHYSICSEVENT_H_
#define KXM_ZARCH_UPDATEPHYSICSEVENT_H_

#include <Zarch/Events/ZarchEvent.h>

namespace kxm {
namespace Zarch {

//! Update physics event.
/*!
 *  \ingroup ZarchEvents
 */
class UpdatePhysicsEvent : public ZarchEvent {
public:
    const EventType &Type() const { return type; }
    
    void Dispatch(EventHandlerCore *handler) const;
    
    static const EventType type;
};
        
}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_UPDATEPHYSICSEVENT_H_
