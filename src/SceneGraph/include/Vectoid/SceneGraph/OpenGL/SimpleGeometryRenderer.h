#ifndef VECTOID_SCENEGRAPH_OPENGL_SIMPLEGEOMETRYRENDERER_H_
#define VECTOID_SCENEGRAPH_OPENGL_SIMPLEGEOMETRYRENDERER_H_

#include <Vectoid/SceneGraph/SimpleGeometryRenderer.h>

#include <vector>
#include <Vectoid/SceneGraph/OpenGL/OpenGL.h>

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

class RenderTarget;

//! Renders simple geometry.
class SimpleGeometryRenderer : public SceneGraph::SimpleGeometryRenderer {
  public:
    friend class RenderTarget;
    
    SimpleGeometryRenderer(const SimpleGeometryRenderer &other) = delete;
    SimpleGeometryRenderer &operator=(const SimpleGeometryRenderer &other) = delete;
    void Render();
    
  private:
    SimpleGeometryRenderer(const std::shared_ptr<SimpleGeometry> &geometry);
  
    int                  numTriangles_;
    std::vector<GLfloat> vertexArray_,
                         colorArray_;
};

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_OPENGL_SIMPLEGEOMETRYRENDERER_H_
