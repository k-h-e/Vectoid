#ifndef VECTOID_SCENEGRAPH_POINTS_H_
#define VECTOID_SCENEGRAPH_POINTS_H_

#include <memory>
#include <Vectoid/Core/Vector.h>
#include <Vectoid/SceneGraph/GeometryInterface.h>

namespace Vectoid {
namespace DataSet {
    class VertexSet;
}
}

namespace Vectoid {
namespace SceneGraph {

//! Renders points.
class Points : public virtual GeometryInterface {
  public:
    Points(const Points &other)            = delete;
    Points &operator=(const Points &other) = delete;
    Points(Points &&other)                 = delete;
    Points &operator=(Points &&other)      = delete;

    void SetColor(const Core::Vector<float> &color);

  protected:
    Points(const std::shared_ptr<DataSet::VertexSet> &points);

    std::shared_ptr<DataSet::VertexSet> points_;
    Core::Vector<float>                 color_;
};

}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_POINTS_H_
