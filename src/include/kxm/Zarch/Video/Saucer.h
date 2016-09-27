#ifndef KXM_ZARCH_VIDEO_SAUCER_H_
#define KXM_ZARCH_VIDEO_SAUCER_H_

#include <kxm/Zarch/Video/Actor.h>

namespace kxm {

namespace Vectoid {
    class CoordSys;
}

namespace Zarch {

class ActorCreationEvent;
class ActorTerminationEvent;
class MoveEvent;

namespace Video {

struct Data;

//! Represents an enemy saucer inside the video sub system.
/*!
 *  \ingroup ZarchVideo
 */
class Saucer : public Actor {
  public:
    Saucer();
    Saucer(const Saucer &other)            = delete;
    Saucer &operator=(const Saucer &other) = delete;
    Saucer(const Saucer &&other)           = delete;
    Saucer &operator=(Saucer &&other)      = delete;
    void GetTransform(Vectoid::Transform *outTransform);
    void GetVelocity(Vectoid::Vector *outVelocity);
    void Handle(const ActorCreationEvent &event);
    void Handle(const ActorTerminationEvent &event);
    void Handle(const MoveEvent &event);
    void ExecuteAction();
    
  private:
    std::shared_ptr<Vectoid::CoordSys> coordSys_;
};

}    // Namespace Video.
}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_VIDEO_SAUCER_H_
