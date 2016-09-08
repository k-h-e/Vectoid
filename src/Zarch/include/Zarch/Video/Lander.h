#ifndef KXM_ZARCH_VIDEO_LANDER_H_
#define KXM_ZARCH_VIDEO_LANDER_H_

#include <memory>
#include <Game/ProcessInterface.h>
#include <Vectoid/Vector.h>
#include <Zarch/EventHandlerCore.h>

namespace kxm {

namespace Vectoid {
    class Camera;
    class CoordSys;
    class Geode;
    class Particles;
}

namespace Zarch {

class MoveEvent;

namespace Video {

struct Data;

//! Represents a lander inside the video sub system.
/*!
 *  \ingroup ZarchVideo
 */
class Lander : public EventHandlerCore, public virtual Game::ProcessInterface {
  public:
    Lander(const std::shared_ptr<Data> &data);
    Lander(const Lander &other)            = delete;
    Lander &operator=(const Lander &other) = delete;
    Lander(const Lander &&other)           = delete;
    Lander &operator=(Lander &&other)      = delete;
    
    
    void AttachToCamera(const std::shared_ptr<Vectoid::Camera> &camera);
    void GetPosition(Vectoid::Vector *outPosition);
    void Handle(const MoveEvent &event);
    void Execute();
    bool Finished();
    
  private:
    std::shared_ptr<Data>               data_;
    std::shared_ptr<Vectoid::CoordSys>  coordSys_;
    std::shared_ptr<Vectoid::Particles> thrusterParticles_;
    std::shared_ptr<Vectoid::Geode>     thrusterParticlesGeode_;
    Vectoid::Vector                     lastLanderPosition_;
    float                               particleTimeCarryOver_;
};

}    // Namespace Video.
}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_VIDEO_LANDER_H_