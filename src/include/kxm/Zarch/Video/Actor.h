#ifndef KXM_ZARCH_VIDEO_ACTOR_H_
#define KXM_ZARCH_VIDEO_ACTOR_H_

#include <memory>
#include <kxm/Core/ActionInterface.h>
#include <kxm/Game/ActorName.h>
#include <kxm/Zarch/EventHandlerCore.h>

namespace kxm {

namespace Vectoid {
    class Transform;
    class Vector;
}

namespace Zarch {

class ActorCreationEvent;

namespace Video {

class Data;

//! Base class to actors inside the video subsystem.
/*!
 *  \ingroup ZarchVideo
 */
class Actor : public EventHandlerCore, public virtual Core::ActionInterface {
  public:
    Actor(const std::shared_ptr<Data> &data);
    // Default copy and move ok.
    virtual void GetTransform(Vectoid::Transform *outTransform) = 0;
    virtual void GetVelocity(Vectoid::Vector *outVelocity) = 0;
    
  protected:
    std::shared_ptr<Data> data_;
};

}    // Namespace Video.
}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_VIDEO_ACTOR_H_
