#ifndef VECTOID_SCENEGRAPH_OPENGL_POINTS_H_
#define VECTOID_SCENEGRAPH_OPENGL_POINTS_H_

#include <Vectoid/SceneGraph/Points.h>

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

//! Renders points.
class Points : public Vectoid::SceneGraph::Points {
  public:
    Points(const std::shared_ptr<DataSet::VertexSet> &points);
    Points(const Points &other)            = delete;
    Points &operator=(const Points &other) = delete;
    Points(Points &&other)                 = delete;
    Points &operator=(Points &&other)      = delete;
    virtual void Render();
};

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_OPENGL_POINTS_H_
