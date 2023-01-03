#ifndef VECTOID_SCENEGRAPH_LITTRIANGLES_H_
#define VECTOID_SCENEGRAPH_LITTRIANGLES_H_

#include <memory>
#include <Vectoid/Core/Vector.h>
#include <Vectoid/SceneGraph/Geometry.h>

namespace Vectoid {
namespace Core {
    class TriangleProviderInterface;
}
}

namespace Vectoid {
namespace SceneGraph {

//! Renders lit triangles.
class LitTriangles : public Geometry {
  public:
    LitTriangles()                                     = delete;
    LitTriangles(const LitTriangles &other)            = delete;
    LitTriangles &operator=(const LitTriangles &other) = delete;
    LitTriangles(LitTriangles &&other)                 = delete;
    LitTriangles &operator=(LitTriangles &&other)      = delete;

    void SetColor(const Core::Vector<float> &color);
    //! Toggles lighting, default is on.
    void EnableLighting(bool enabled);
    //! Toggles depth test, default is on.
    void EnableDepthTest(bool enabled);

  protected:
    LitTriangles(const std::shared_ptr<Context> &context,
                 const std::shared_ptr<Core::TriangleProviderInterface> &triangleProvider);

    std::shared_ptr<Core::TriangleProviderInterface> triangleProvider_;
    Core::Vector<float>                              color_;
    bool                                             lightingEnabled_;
    bool                                             depthTestEnabled_;
};

}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_LITTRIANGLES_H_
