#ifndef KXM_ZARCH_VIDEO_VULKAN_RENDERTARGET_H_
#define KXM_ZARCH_VIDEO_VULKAN_RENDERTARGET_H_

#include <kxm/Zarch/Video/RenderTargetInterface.h>
#include <kxm/Vectoid/Vulkan/RenderTarget.h>

namespace kxm {
namespace Zarch {
namespace Video {
namespace Vulkan {

//! Render target interface, extended to include Zarch-specific graphics resources.
/*!
 *  \ingroup ZarchVideoVulkan
 */
class RenderTarget : public virtual kxm::Zarch::Video::RenderTargetInterface,
                     public Vectoid::Vulkan::RenderTarget {
  public:
    RenderTarget(void *view);
    RenderTarget(const RenderTarget &other) = delete;
    RenderTarget &operator=(const RenderTarget &other) = delete;
    virtual std::shared_ptr<kxm::Zarch::Video::SimpleGeometryRenderer> NewSimpleGeometryRenderer(
        const std::shared_ptr<SimpleGeometry> &geometry);
    virtual std::shared_ptr<kxm::Zarch::Video::TerrainRenderer> NewTerrainRenderer(
        const std::shared_ptr<Terrain> &terrain, const std::shared_ptr<MapParameters> &mapParameters);
};

}    // Namespace Vulkan.
}    // Namespace Video.
}    // Namespace Zarch.
}    // Namespace kxm.

#endif    KXM_ZARCH_VIDEO_VULKAN_RENDERTARGET_H_

