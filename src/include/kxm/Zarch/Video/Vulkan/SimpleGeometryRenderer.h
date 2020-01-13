#ifndef KXM_ZARCH_VIDEO_VULKAN_SIMPLEGEOMETRYRENDERER_H_
#define KXM_ZARCH_VIDEO_VULKAN_SIMPLEGEOMETRYRENDERER_H_

#include <kxm/Zarch/Video/SimpleGeometryRenderer.h>

#include <vector>
#include <kxm/Vectoid/Vulkan/BufferInfo.h>

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
    ~SimpleGeometryRenderer();
    void Render();
    static void GetVertexInputInfo(VkVertexInputBindingDescription *binding,
                                   VkVertexInputAttributeDescription *attributes);
    
  private:
    SimpleGeometryRenderer(const std::shared_ptr<Vectoid::Vulkan::Context> &context,
                           const std::shared_ptr<SimpleGeometry> &geometry);
    void createResources();
    void freeResources();
    
    std::shared_ptr<Vectoid::Vulkan::Context> context_;
    kxm::Vectoid::Vulkan::BufferInfo          vertexBuffer_;
    bool                                      haveResources_;
};

}    // Namespace Vulkan.
}    // Namespace Video.
}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_VIDEO_VULKAN_SIMPLEGEOMETRYRENDERER_H_
