#ifndef VECTOID_SCENEGRAPH_LITTRIANGLES_H_
#define VECTOID_SCENEGRAPH_LITTRIANGLES_H_

#include <memory>
#include <Vectoid/SceneGraph/GeometryInterface.h>

namespace Vectoid {
namespace Core {
    class TriangleProviderInterface;
}
}

namespace Vectoid {
namespace SceneGraph {

//! Renders lit triangles.
/*!
 *  \ingroup Vectoid
 */
class LitTriangles : public virtual GeometryInterface {
  public:
    LitTriangles(const LitTriangles &other)            = delete;
    LitTriangles &operator=(const LitTriangles &other) = delete;
    LitTriangles(LitTriangles &&other)                 = delete;
    LitTriangles &operator=(LitTriangles &&other)      = delete;

  protected:
    LitTriangles(const std::shared_ptr<Core::TriangleProviderInterface> &triangleProvider);

    std::shared_ptr<Core::TriangleProviderInterface> triangleProvider_;
};

}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_LITTRIANGLES_H_
