#ifndef VECTOID_SCENEGRAPH_OPENGL_LITTRIANGLES_H_
#define VECTOID_SCENEGRAPH_OPENGL_LITTRIANGLES_H_

#include <Vectoid/SceneGraph/LitTriangles.h>

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

class Context;
class RenderTarget;

//! Renders lit triangles.
class LitTriangles : public Vectoid::SceneGraph::LitTriangles {
  public:
    LitTriangles()                                     = delete;
    LitTriangles(const std::shared_ptr<Context> &context,
                 const std::shared_ptr<Core::TriangleProviderInterface> &triangleProvider);
    LitTriangles(const LitTriangles &other)            = delete;
    LitTriangles &operator=(const LitTriangles &other) = delete;
    LitTriangles(LitTriangles &&other)                 = delete;
    LitTriangles &operator=(LitTriangles &&other)      = delete;

    void Render() override;
};

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // KXM_VECTOID_LITTRIANGLES_H_
