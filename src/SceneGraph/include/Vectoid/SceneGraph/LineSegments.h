#ifndef VECTOID_SCENEGRAPH_LINESEGMENTS_H_
#define VECTOID_SCENEGRAPH_LINESEGMENTS_H_

#include <memory>
#include <Vectoid/SceneGraph/GeometryInterface.h>

namespace Vectoid {
namespace Core {
    class LineSegmentProviderInterface;
}
}

namespace Vectoid {
namespace SceneGraph {

//! Renders line segments.
/*!
 *  \ingroup Vectoid
 */
class LineSegments : public virtual GeometryInterface {
  public:
    LineSegments(const LineSegments &other)            = delete;
    LineSegments &operator=(const LineSegments &other) = delete;
    LineSegments(LineSegments &&other)                 = delete;
    LineSegments &operator=(LineSegments &&other)      = delete;

  protected:
    LineSegments(const std::shared_ptr<Core::LineSegmentProviderInterface> &lineSegmentProvider);

    std::shared_ptr<Core::LineSegmentProviderInterface> lineSegmentProvider_;
};

}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_LINESEGMENTS_H_