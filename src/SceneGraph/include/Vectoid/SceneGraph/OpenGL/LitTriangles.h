#ifndef VECTOID_SCENEGRAPH_OPENGL_LITTRIANGLES_H_
#define VECTOID_SCENEGRAPH_OPENGL_LITTRIANGLES_H_

#include <Vectoid/SceneGraph/LitTriangles.h>

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

//! Renders lit triangles.
/*!
 *  \ingroup VectoidOpenGL
 */
class LitTriangles : public Vectoid::SceneGraph::LitTriangles {
  public:
    LitTriangles(const std::shared_ptr<Core::TriangleProviderInterface> &triangleProvider);
    LitTriangles(const LitTriangles &other)            = delete;
    LitTriangles &operator=(const LitTriangles &other) = delete;
    LitTriangles(LitTriangles &&other)                 = delete;
    LitTriangles &operator=(LitTriangles &&other)      = delete;
    virtual void Render();
};

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // KXM_VECTOID_LITTRIANGLES_H_
