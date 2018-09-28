#ifndef KXM_VECTOID_OPENGL_PERSPECTIVEPROJECTION_H_
#define KXM_VECTOID_OPENGL_PERSPECTIVEPROJECTION_H_

#include <kxm/Vectoid/PerspectiveProjection.h>

namespace kxm {
namespace Vectoid {
namespace OpenGL {

class RenderTarget;

//! Perspective screen projection, defining a frustum-shaped viewing volume.
/*! 
 *  \ingroup VectoidOpenGL
 */ 
class PerspectiveProjection : public Vectoid::PerspectiveProjection {
  public:
    friend class RenderTarget;
    
    PerspectiveProjection(const PerspectiveProjection &other) = delete;
    PerspectiveProjection &operator=(const PerspectiveProjection &other) = delete;
    void Render();
    
  private:
    PerspectiveProjection();
};

}    // Namespace OpenGL.
}    // Namespace Vectoid.
}    // Namespace kxm.

#endif    // KXM_VECTOID_OPENGL_PERSPECTIVEPROJECTION_H_
