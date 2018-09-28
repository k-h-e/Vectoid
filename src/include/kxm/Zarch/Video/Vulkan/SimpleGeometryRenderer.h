#ifndef KXM_ZARCH_VIDEO_VULKAN_SIMPLEGEOMETRYRENDERER_H_
#define KXM_ZARCH_VIDEO_VULKAN_SIMPLEGEOMETRYRENDERER_H_

#include <kxm/Zarch/Video/SimpleGeometryRenderer.h>

#include <vector>

namespace kxm {

namespace Vectoid {
namespace Vulkan {

class Context;

}
}

namespace Zarch {
namespace Video {
namespace Vulkan {

class RenderTarget;

//! Renders simple geometry.
/*!
 *  \ingroup ZarchVideoVulkan
 */
class SimpleGeometryRenderer : public Video::SimpleGeometryRenderer {
  public:
    friend class RenderTarget;
  
    SimpleGeometryRenderer(const SimpleGeometryRenderer &other) = delete;
    SimpleGeometryRenderer &operator=(const SimpleGeometryRenderer &other) = delete;
    void Render();
    
  private:
    SimpleGeometryRenderer(const std::shared_ptr<Vectoid::Vulkan::Context> &context,
                           const std::shared_ptr<SimpleGeometry> &geometry);
    
    std::shared_ptr<Vectoid::Vulkan::Context> context_;
};

}    // Namespace Vulkan.
}    // Namespace Video.
}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_VIDEO_VULKAN_SIMPLEGEOMETRYRENDERER_H_
