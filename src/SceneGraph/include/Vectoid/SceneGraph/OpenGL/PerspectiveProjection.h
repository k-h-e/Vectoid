#ifndef VECTOID_SCENEGRAPH_OPENGL_PERSPECTIVEPROJECTION_H_
#define VECTOID_SCENEGRAPH_OPENGL_PERSPECTIVEPROJECTION_H_

#include <Vectoid/SceneGraph/PerspectiveProjection.h>

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

class RenderTarget;

//! Perspective screen projection, defining a frustum-shaped viewing volume.
class PerspectiveProjection : public Vectoid::SceneGraph::PerspectiveProjection {
  public:
    friend class RenderTarget;
    
    PerspectiveProjection(const PerspectiveProjection &other) = delete;
    PerspectiveProjection &operator=(const PerspectiveProjection &other) = delete;

    void RenderPre() override;
    
  private:
    PerspectiveProjection();
};

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_OPENGL_PERSPECTIVEPROJECTION_H_
