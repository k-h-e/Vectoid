#ifndef KXM_ZARCH_VIDEO_LANDER_H_
#define KXM_ZARCH_VIDEO_LANDER_H_

#include <memory>
#include <kxm/Core/Interface.h>

namespace kxm {

namespace Vectoid {
    class CoordSys;
}

namespace Zarch {
namespace Video {

//! Represents a lander inside the video sub system.
/*!
 *  \ingroup ZarchVideo
 */
class Lander : public virtual Core::Interface {
  public:
    Lander();
    Lander(const Lander &other)            = delete;
    Lander &operator=(const Lander &other) = delete;
    Lander(const Lander &&other)           = delete;
    Lander &operator=(Lander &&other)      = delete;
    const std::shared_ptr<Vectoid::CoordSys> &RootNode() const;
    
  private:
    std::shared_ptr<Vectoid::CoordSys> coordSys_;
};

}    // Namespace Video.
}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_VIDEO_LANDER_H_