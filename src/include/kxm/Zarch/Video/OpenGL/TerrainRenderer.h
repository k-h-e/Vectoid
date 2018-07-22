#ifndef KXM_ZARCH_VIDEO_OPENGL_TERRAINRENDERER_H_
#define KXM_ZARCH_VIDEO_OPENGL_TERRAINRENDERER_H_

#include <kxm/Zarch/Video/TerrainRenderer.h>

#include <kxm/Vectoid/OpenGL/OpenGL.h>

namespace kxm {
namespace Zarch {
namespace Video {
namespace OpenGL {

//! Renders the terrain.
/*!
 *  \ingroup ZarchVideoOpenGL
 */
class TerrainRenderer : public Video::TerrainRenderer {
  public:
    TerrainRenderer(const std::shared_ptr<Terrain> &terrain,
                    const std::shared_ptr<MapParameters> &mapParameters);
    TerrainRenderer(const TerrainRenderer &other) = delete;
    TerrainRenderer &operator=(const TerrainRenderer &other) = delete;
    void Render();
    
  private:
    std::vector<GLfloat> vertices_;
};

}    // Namespace OpenGL.
}    // Namespace Video.
}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_VIDEO_OPENGL_TERRAINRENDERER_H_
