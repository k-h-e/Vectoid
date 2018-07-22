#ifndef KXM_ZARCH_VIDEO_METAL_RENDERTARGET_H_
#define KXM_ZARCH_VIDEO_METAL_RENDERTARGET_H_

#include <kxm/Zarch/Video/RenderTargetInterface.h>
#include <kxm/Vectoid/Metal/RenderTarget.h>

namespace kxm {
namespace Zarch {
namespace Video {
namespace Metal {

//! Render target interface, extended to include Zarch-specific graphics resources.
/*!
 *  \ingroup ZarchVideoMetal
 */
class RenderTarget : public virtual kxm::Zarch::Video::RenderTargetInterface,
                     public Vectoid::Metal::RenderTarget {
  public:
    RenderTarget(MTKView *metalView);
    RenderTarget(const RenderTarget &other) = delete;
    RenderTarget &operator=(const RenderTarget &other) = delete;
    virtual std::shared_ptr<SimpleGeometryRenderer> NewSimpleGeometryRenderer(
        const std::shared_ptr<SimpleGeometry> &geometry);
    virtual std::shared_ptr<TerrainRenderer> NewTerrainRenderer(const std::shared_ptr<Terrain> &terrain,
                                                                const std::shared_ptr<MapParameters> &mapParameters);
};

}    // Namespace Metal.
}    // Namespace Video.
}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_VIDEO_METAL_RENDERTARGET_H_

