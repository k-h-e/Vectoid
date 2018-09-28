#ifndef KXM_ZARCH_VIDEO_METAL_TERRAINRENDERER_H_
#define KXM_ZARCH_VIDEO_METAL_TERRAINRENDERER_H_

#include <memory>
#include <kxm/Zarch/Video/TerrainRenderer.h>

namespace kxm {

namespace Vectoid {
namespace Metal {

class Context;

}
}

namespace Zarch {
namespace Video {
namespace Metal {

class RenderTarget;

//! Renders the terrain.
/*!
 *  \ingroup ZarchVideoMetal
 */
class TerrainRenderer : public Video::TerrainRenderer {
  public:
    friend class RenderTarget;
    
    TerrainRenderer(const TerrainRenderer &other) = delete;
    TerrainRenderer &operator=(const TerrainRenderer &other) = delete;
    void Render();
    
  private:
    TerrainRenderer(const std::shared_ptr<Vectoid::Metal::Context> &context, const std::shared_ptr<Terrain> &terrain,
                    const std::shared_ptr<MapParameters> &mapParameters);
    
    std::shared_ptr<Vectoid::Metal::Context> context_;
};

}    // Namespace Metal.
}    // Namespace Video.
}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_VIDEO_METAL_TERRAINRENDERER_H_

