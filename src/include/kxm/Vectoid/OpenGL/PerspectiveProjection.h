#ifndef KXM_VECTOID_OPENGL_PERSPECTIVEPROJECTION_H_
#define KXM_VECTOID_OPENGL_PERSPECTIVEPROJECTION_H_

#include <kxm/Vectoid/PerspectiveProjection.h>

namespace kxm {
namespace Vectoid {
namespace OpenGL {

//! Perspective screen projection, defining a frustum-shaped viewing volume.
/*! 
 *  \ingroup VectoidOpenGL
 */ 
class PerspectiveProjection : public Vectoid::PerspectiveProjection {
  public:
    PerspectiveProjection();
    PerspectiveProjection(const PerspectiveProjection &other) = delete;
    PerspectiveProjection &operator=(const PerspectiveProjection &other) = delete;
    void Render(RenderContext *context);
};

}    // Namespace OpenGL.
}    // Namespace Vectoid.
}    // Namespace kxm.

#endif    // KXM_VECTOID_OPENGL_PERSPECTIVEPROJECTION_H_
