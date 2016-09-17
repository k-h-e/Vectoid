#ifndef KXM_ZARCH_TIMEEVENT_H_
#define KXM_ZARCH_TIMEEVENT_H_

#include <kxm/Zarch/Events/ZarchEvent.h>

namespace kxm {
namespace Zarch {

//! Time event.
/*!
 *  \ingroup ZarchEvents
 */
class TimeEvent : public ZarchEvent {
  public:
    TimeEvent();
    TimeEvent(float aDeltaTimeS);
    const EventType &Type() const { return type; }
    
    void Dispatch(EventHandlerCore *handler) const;
    void Serialize(Core::Buffer *targetBuffer) const;
    void Deserialize(Core::Buffer::Reader *bufferReader);
    
    static const EventType type;
    
    float deltaTimeS;
};
        
}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_TIMEEVENT_H_
