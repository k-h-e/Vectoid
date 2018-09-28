#ifndef KXM_VECTOID_OPENGL_CAMERA_H_
#define KXM_VECTOID_OPENGL_CAMERA_H_

#include <kxm/Vectoid/Camera.h>

namespace kxm {
namespace Vectoid {
namespace OpenGL {

class RenderTarget;

//! This scene graph node represents a camera.
/*! 
 *  \ingroup VectoidOpenGL
 */ 
class Camera : public Vectoid::Camera {
  public:
    friend class RenderTarget;
    
    Camera(const Camera &other) = delete;
    Camera &operator=(const Camera &other) = delete;
    void Render();
    
  private:
    Camera();
};

}    // Namespace OpenGL.
}    // Namespace Vectoid.
}    // Namespace kxm.

#endif    // KXM_VECTOID_OPENGL_CAMERA_H_
