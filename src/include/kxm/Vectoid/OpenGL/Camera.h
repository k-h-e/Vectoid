#ifndef KXM_VECTOID_OPENGL_CAMERA_H_
#define KXM_VECTOID_OPENGL_CAMERA_H_

#include <kxm/Vectoid/Camera.h>

namespace kxm {
namespace Vectoid {
namespace OpenGL {

//! This scene graph node represents a camera.
/*! 
 *  \ingroup VectoidOpenGL
 */ 
class Camera : public Vectoid::Camera {
  public:
    Camera();
    Camera(const Camera &other) = delete;
    Camera &operator=(const Camera &other) = delete;
    void Render();
};

}    // Namespace OpenGL.
}    // Namespace Vectoid.
}    // Namespace kxm.

#endif    // KXM_VECTOID_OPENGL_CAMERA_H_
