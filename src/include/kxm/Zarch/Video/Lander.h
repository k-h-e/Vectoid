#ifndef KXM_ZARCH_VIDEO_LANDER_H_
#define KXM_ZARCH_VIDEO_LANDER_H_

#include <memory>
#include <kxm/Vectoid/Vector.h>
#include <kxm/Zarch/Video/Actor.h>

namespace kxm {

namespace Vectoid {
    class Camera;
    class CoordSys;
}

namespace Zarch {

class ActorCreationEvent;
class ActorTerminationEvent;
class ControlsEvent;
class MoveEvent;
class VelocityEvent;

namespace Video {

struct Data;

//! Represents a lander inside the video sub system.
/*!
 *  \ingroup ZarchVideo
 */
class Lander : public Actor {
  public:
    Lander(const std::shared_ptr<Data> &data);
    Lander(const Lander &other)            = delete;
    Lander &operator=(const Lander &other) = delete;
    Lander(const Lander &&other)           = delete;
    Lander &operator=(Lander &&other)      = delete;
    
    void GetTransform(Vectoid::Transform *outTransform);
    void GetVelocity(Vectoid::Vector *outVelocity);
    void Handle(const ActorCreationEvent &event);
    void Handle(const ActorTerminationEvent &event);
    void Handle(const ControlsEvent &event);
    void Handle(const MoveEvent &event);
    void Handle(const VelocityEvent &event);
    void ExecuteAction();
    
  private:
    std::shared_ptr<Vectoid::CoordSys>  coordSys_;
    Vectoid::Vector                     velocity_,
                                        lastPosition_;
    bool                                thrusterActive_;
    float                               particleTimeCarryOver_;
    bool                                hasFocus_;
};

}    // Namespace Video.
}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_VIDEO_LANDER_H_
