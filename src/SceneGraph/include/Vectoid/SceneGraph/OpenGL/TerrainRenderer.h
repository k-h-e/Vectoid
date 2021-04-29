#ifndef VECTOID_SCENEGRAPH_OPENGL_TERRAINRENDERER_H_
#define VECTOID_SCENEGRAPH_OPENGL_TERRAINRENDERER_H_

#include <Vectoid/SceneGraph/TerrainRenderer.h>

#include <Vectoid/SceneGraph/OpenGL/OpenGL.h>

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

class RenderTarget;

//! Renders the terrain.
class TerrainRenderer : public SceneGraph::TerrainRenderer {
  public:
    friend class RenderTarget;
  
    TerrainRenderer(const TerrainRenderer &other) = delete;
    TerrainRenderer &operator=(const TerrainRenderer &other) = delete;
    void Render();
    
  private:
    TerrainRenderer(const std::shared_ptr<Terrain> &terrain,
                    const std::shared_ptr<MapParameters> &mapParameters);
    
    std::vector<GLfloat> vertices_;
};

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_OPENGL_TERRAINRENDERER_H_
