#ifndef VECTOID_SCENEGRAPH_OPENGL_COORDSYS_H_
#define VECTOID_SCENEGRAPH_OPENGL_COORDSYS_H_

#include <Vectoid/SceneGraph/CoordSys.h>

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

class Context;
class RenderTarget;

//! This scene graph node sets up a local coordinate system for its children.
class CoordSys : public Vectoid::SceneGraph::CoordSys {
  public:
    CoordSys()                                 = delete;
    CoordSys(const std::shared_ptr<Context> &context);
    CoordSys(const CoordSys &other)            = delete;
    CoordSys &operator=(const CoordSys &other) = delete;
    CoordSys(CoordSys &&other)                 = delete;
    CoordSys &operator=(CoordSys &&other)      = delete;

    void RenderPre() override;
    void RenderPost() override;
};

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_OPENGL_COORDSYS_H_
