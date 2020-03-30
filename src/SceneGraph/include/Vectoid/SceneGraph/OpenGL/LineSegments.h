#ifndef VECTOID_SCENEGRAPH_OPENGL_LINESEGMENTS_H_
#define VECTOID_SCENEGRAPH_OPENGL_LINESEGMENTS_H_

#include <Vectoid/SceneGraph/LineSegments.h>

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

//! Renders line segments.
/*!
 *  \ingroup VectoidOpenGL
 */
class LineSegments : public Vectoid::SceneGraph::LineSegments {
  public:
    LineSegments(const std::shared_ptr<Core::LineSegmentProviderInterface> &lineSegmentProvider);
    LineSegments(const LineSegments &other)            = delete;
    LineSegments &operator=(const LineSegments &other) = delete;
    LineSegments(LineSegments &&other)                 = delete;
    LineSegments &operator=(LineSegments &&other)      = delete;
    virtual void Render();
};

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_OPENGL_LINESEGMENTS_H_
