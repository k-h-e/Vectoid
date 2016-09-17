#ifndef KXM_ZARCH_VIDEO_LANDER_H_
#define KXM_ZARCH_VIDEO_LANDER_H_

#include <memory>
#include <kxm/Core/ActionInterface.h>
#include <kxm/Vectoid/Vector.h>
#include <kxm/Zarch/EventHandlerCore.h>

namespace kxm {

namespace Vectoid {
    class Camera;
    class CoordSys;
    class Geode;
    class Particles;
}

namespace Zarch {

class ActorCreationEvent;
class MoveEvent;
class VelocityEvent;
class AccelerationEvent;

namespace Video {

struct Data;

//! Represents a lander inside the video sub system.
/*!
 *  \ingroup ZarchVideo
 */
class Lander : public EventHandlerCore, public virtual Core::ActionInterface {
  public:
    Lander();
    Lander(const Lander &other)            = delete;
    Lander &operator=(const Lander &other) = delete;
    Lander(const Lander &&other)           = delete;
    Lander &operator=(Lander &&other)      = delete;
    
    void Reset(bool hasFocus, const std::shared_ptr<Data> &data);
    void Handle(const ActorCreationEvent &event);
    void Handle(const MoveEvent &event);
    void Handle(const VelocityEvent &event);
    void Handle(const AccelerationEvent &event);
    void ExecuteAction();
    
  private:
    std::shared_ptr<Data>               data_;    // Null when default-initialized!
    std::shared_ptr<Vectoid::CoordSys>  coordSys_;
    std::shared_ptr<Vectoid::Particles> thrusterParticles_;
    std::shared_ptr<Vectoid::Geode>     thrusterParticlesGeode_;
    Vectoid::Vector                     lastPosition_,
                                        velocity_;
    bool                                thrusterActive_;
    float                               particleTimeCarryOver_;
    bool                                hasFocus_;
};

}    // Namespace Video.
}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_VIDEO_LANDER_H_
