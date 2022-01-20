#ifndef VECTOID_SCENEGRAPH_OPENGL_LINESEGMENTS_H_
#define VECTOID_SCENEGRAPH_OPENGL_LINESEGMENTS_H_

#include <Vectoid/SceneGraph/LineSegments.h>
#include <Vectoid/SceneGraph/OpenGL/Context.h>

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

class Context;
class RenderTarget;

//! Renders line segments.
class LineSegments : public Vectoid::SceneGraph::LineSegments {
  public:
    LineSegments()                                     = delete;
    LineSegments(const std::shared_ptr<Context> &context,
                 const std::shared_ptr<Core::LineSegmentProviderInterface> &lineSegmentProvider);
    LineSegments(const LineSegments &other)            = delete;
    LineSegments &operator=(const LineSegments &other) = delete;
    LineSegments(LineSegments &&other)                 = delete;
    LineSegments &operator=(LineSegments &&other)      = delete;
    ~LineSegments();

    void Render() override;

  private:
    Context *Context() { return static_cast<class Context *>(context_.get()); }
    std::optional<GLuint> GenerateVBO();

    int vboSlot_;
    int numSegments_;    // Valid <=> VBO present.
};

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_OPENGL_LINESEGMENTS_H_
