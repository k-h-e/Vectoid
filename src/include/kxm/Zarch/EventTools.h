#ifndef KXM_ZARCH_EVENTTOOLS_H_
#define KXM_ZARCH_EVENTTOOLS_H_

#include <kxm/Game/ActorName.h>
#include <kxm/Vectoid/Transform.h>
#include <kxm/Zarch/Events/ActorCreationEvent.h>

using namespace kxm::Game;
using namespace kxm::Vectoid;
using namespace kxm::Zarch;

namespace kxm {
namespace Zarch {

//! Event tools.
/*!
 *  \ingroup Zarch
 */
class EventTools {
  public:
    //! If the passed-in \ref ActorCreationEvent specifies initial transform and velocity relative to a launching actor,
    //! this method converts both into the world coordinate system using the specified launching actor transform and
    //! velocity.
    static inline void ResolveInitialTransformAndVelocity(
                           ActorCreationEvent *event, const Transform &launchingActorTransform,
                           const Vector &launchingActorVelocity);
};

void EventTools::ResolveInitialTransformAndVelocity(ActorCreationEvent *event, const Transform &launchingActorTransform,
                                                    const Vector &launchingActorVelocity) {
    if (!event->launchingActor.IsNone()) {
        Transform transform = launchingActorTransform;
        transform.SetTranslationPart(Vector());
        transform.ApplyTo(&event->initialVelocity);
        event->initialVelocity += launchingActorVelocity;
        
        event->initialTransform.Append(launchingActorTransform);
        
        event->launchingActor = ActorName();
    }
}

}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_EVENTTOOLS_H_
