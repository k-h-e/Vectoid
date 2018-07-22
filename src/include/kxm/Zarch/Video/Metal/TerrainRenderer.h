#ifndef KXM_ZARCH_VIDEO_METAL_TERRAINRENDERER_H_
#define KXM_ZARCH_VIDEO_METAL_TERRAINRENDERER_H_

#include <kxm/Zarch/Video/TerrainRenderer.h>

namespace kxm {
namespace Zarch {
namespace Video {
namespace Metal {

//! Renders the terrain.
/*!
 *  \ingroup ZarchVideoMetal
 */
class TerrainRenderer : public Video::TerrainRenderer {
  public:
    TerrainRenderer(std::shared_ptr<Terrain> terrain,
                    std::shared_ptr<MapParameters> mapParameters);
    TerrainRenderer(const TerrainRenderer &other) = delete;
    TerrainRenderer &operator=(const TerrainRenderer &other) = delete;
    void Render();
};

}    // Namespace Metal.
}    // Namespace Video.
}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_VIDEO_METAL_TERRAINRENDERER_H_

