#ifndef KXM_ZARCH_VIDEO_OPENGL_RENDERTARGET_H_
#define KXM_ZARCH_VIDEO_OPENGL_RENDERTARGET_H_

#include <kxm/Zarch/Video/RenderTargetInterface.h>
#include <kxm/Vectoid/OpenGL/RenderTarget.h>

namespace kxm {
namespace Zarch {
namespace Video {
namespace OpenGL {

//! Render target interface, extended to include Zarch-specific graphics resources.
/*!
 *  \ingroup ZarchVideoOpenGL
 */
class RenderTarget : public virtual kxm::Zarch::Video::RenderTargetInterface,
                     public Vectoid::OpenGL::RenderTarget {
  public:
    RenderTarget();
    RenderTarget(const RenderTarget &other) = delete;
    RenderTarget &operator=(const RenderTarget &other) = delete;
    virtual std::shared_ptr<SimpleGeometryRenderer> NewSimpleGeometryRenderer(
        const std::shared_ptr<SimpleGeometry> &geometry);
    virtual std::shared_ptr<TerrainRenderer> NewTerrainRenderer(std::shared_ptr<Terrain> terrain,
                                                                std::shared_ptr<MapParameters> mapParameters);
};

}    // Namespace OpenGL.
}    // Namespace Video.
}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_VIDEO_OPENGL_RENDERTARGET_H_
