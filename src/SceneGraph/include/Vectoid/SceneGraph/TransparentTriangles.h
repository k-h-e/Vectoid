#ifndef VECTOID_SCENEGRAPH_TRANSPARENTTRIANGLES_H_
#define VECTOID_SCENEGRAPH_TRANSPARENTTRIANGLES_H_

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

//! Renders transparent triangles.
class TransparentTriangles : public Geometry {
  public:
    TransparentTriangles()                                             = delete;
    TransparentTriangles(const TransparentTriangles &other)            = delete;
    TransparentTriangles &operator=(const TransparentTriangles &other) = delete;
    TransparentTriangles(TransparentTriangles &&other)                 = delete;
    TransparentTriangles &operator=(TransparentTriangles &&other)      = delete;

    void SetColor(const Core::Vector<float> &color);
    void SetAlpha(float alpha);

  protected:
    TransparentTriangles(const std::shared_ptr<Context> &context,
                         const std::shared_ptr<Core::TriangleProviderInterface> &triangleProvider);

    std::shared_ptr<Core::TriangleProviderInterface> triangleProvider_;
    Core::Vector<float>                              color_;
    float                                            alpha_;
};

}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_TRANSPARENTTRIANGLES_H_
