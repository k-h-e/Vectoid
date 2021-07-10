#ifndef VECTOID_SCENEGRAPH_OPENGL_LITCOLORCODEDTRIANGLES_H_
#define VECTOID_SCENEGRAPH_OPENGL_LITCOLORCODEDTRIANGLES_H_

#include <Vectoid/SceneGraph/LitColorCodedTriangles.h>

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

//! Renders lit, color-coded triangles.
class LitColorCodedTriangles : public Vectoid::SceneGraph::LitColorCodedTriangles {
  public:
    LitColorCodedTriangles(const std::shared_ptr<Core::TriangleProviderInterface> &triangleProvider);
    LitColorCodedTriangles(const LitColorCodedTriangles &other)            = delete;
    LitColorCodedTriangles &operator=(const LitColorCodedTriangles &other) = delete;
    LitColorCodedTriangles(LitColorCodedTriangles &&other)                 = delete;
    LitColorCodedTriangles &operator=(LitColorCodedTriangles &&other)      = delete;
    virtual void Render();

  private:
    Vectoid::Core::Vector<float> GetColor(const Vectoid::Core::Vector<float> &vertex);
};

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_OPENGL_LITCOLORCODEDTRIANGLES_H_
