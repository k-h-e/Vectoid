#ifndef KXM_VECTOID_VULKAN_COORDSYS_H_
#define KXM_VECTOID_VULKAN_COORDSYS_H_

#include <kxm/Vectoid/CoordSys.h>

namespace kxm {
namespace Vectoid {
namespace Vulkan {

class Context;

//! This scene graph node sets up a local coordinate system for its children.
/*! 
 *  \ingroup VectoidVulkan
 */ 
class CoordSys : public Vectoid::CoordSys {
  public:
    CoordSys(const std::shared_ptr<Context> &context);
    CoordSys(const CoordSys &other) = delete;
    CoordSys &operator=(const CoordSys &other) = delete;
    void Render();

  private:
    std::shared_ptr<Context> context_;
};

}    // Namespace Vulkan.
}    // Namespace Vectoid.
}    // Namespace kxm.

#endif    // KXM_VECTOID_VULKAN_COORDSYS_H_
