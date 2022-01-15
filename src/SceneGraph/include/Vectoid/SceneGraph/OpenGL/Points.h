#ifndef VECTOID_SCENEGRAPH_OPENGL_POINTS_H_
#define VECTOID_SCENEGRAPH_OPENGL_POINTS_H_

#include <Vectoid/SceneGraph/Points.h>

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

class Context;
class RenderTarget;

//! Renders points.
class Points : public Vectoid::SceneGraph::Points {
  public:
    Points()                               = delete;
    Points(const std::shared_ptr<Context> &context, const std::shared_ptr<DataSet::Points> &points);
    Points(const Points &other)            = delete;
    Points &operator=(const Points &other) = delete;
    Points(Points &&other)                 = delete;
    Points &operator=(Points &&other)      = delete;

    void Render() override;
};

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_OPENGL_POINTS_H_
