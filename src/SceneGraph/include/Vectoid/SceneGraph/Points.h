#ifndef VECTOID_SCENEGRAPH_POINTS_H_
#define VECTOID_SCENEGRAPH_POINTS_H_

#include <memory>
#include <Vectoid/Core/Vector.h>
#include <Vectoid/SceneGraph/Geometry.h>

namespace Vectoid {
namespace DataSet {
    class Points;
}
}

namespace Vectoid {
namespace SceneGraph {

//! Renders points.
class Points : public Geometry {
  public:
    Points()                               = delete;
    Points(const DataSet::Points &other)   = delete;
    Points &operator=(const Points &other) = delete;
    Points(Points &&other)                 = delete;
    Points &operator=(Points &&other)      = delete;

    void SetColor(const Core::Vector<float> &color);

  protected:
    Points(const std::shared_ptr<Context> &context, const std::shared_ptr<DataSet::Points> &points);

    std::shared_ptr<DataSet::Points> points_;
    Core::Vector<float>              color_;
};

}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_POINTS_H_
