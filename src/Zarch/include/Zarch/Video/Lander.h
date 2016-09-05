#ifndef KXM_ZARCH_VIDEO_LANDER_H_
#define KXM_ZARCH_VIDEO_LANDER_H_

#include <memory>
#include <kxm/Core/Interface.h>
#include <Zarch/EventHandlerCore.h>

namespace kxm {

namespace Vectoid {
    class Camera;
    class CoordSys;
}

namespace Zarch {

class MoveEvent;

namespace Video {

//! Represents a lander inside the video sub system.
/*!
 *  \ingroup ZarchVideo
 */
class Lander : public EventHandlerCore {
  public:
    Lander(const std::shared_ptr<Vectoid::Camera> &camera);
    Lander(const Lander &other)            = delete;
    Lander &operator=(const Lander &other) = delete;
    Lander(const Lander &&other)           = delete;
    Lander &operator=(Lander &&other)      = delete;
    const std::shared_ptr<Vectoid::CoordSys> &RootNode() const;
    void Handle(const MoveEvent &event);
    
  private:
    std::shared_ptr<Vectoid::CoordSys> coordSys_;
    std::shared_ptr<Vectoid::Camera>   camera_;
};

}    // Namespace Video.
}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_VIDEO_LANDER_H_