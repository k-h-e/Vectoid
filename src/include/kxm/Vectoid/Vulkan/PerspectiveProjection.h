#ifndef KXM_VECTOID_VULKAN_PERSPECTIVEPROJECTION_H_
#define KXM_VECTOID_VULKAN_PERSPECTIVEPROJECTION_H_

#include <kxm/Vectoid/PerspectiveProjection.h>

#include <kxm/Vectoid/FullTransform.h>

namespace kxm {
namespace Vectoid {
namespace Vulkan {

class RenderTarget;
class Context;

//! Perspective screen projection, defining a frustum-shaped viewing volume.
/*! 
 *  \ingroup VectoidVulkan
 */ 
class PerspectiveProjection : public Vectoid::PerspectiveProjection {
  public:
    friend class RenderTarget;
    
    PerspectiveProjection(const PerspectiveProjection &other) = delete;
    PerspectiveProjection &operator=(const PerspectiveProjection &other) = delete;
    void Render();
    
  private:
    PerspectiveProjection(const std::shared_ptr<Context> &context);
    
    std::shared_ptr<Context> context_;
    FullTransform transform_;
};

}    // Namespace Vulkan.
}    // Namespace Vectoid.
}    // Namespace kxm.

#endif    // KXM_VECTOID_VULKAN_PERSPECTIVEPROJECTION_H_
