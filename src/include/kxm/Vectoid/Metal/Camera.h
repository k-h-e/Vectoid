#ifndef KXM_VECTOID_METAL_CAMERA_H_
#define KXM_VECTOID_METAL_CAMERA_H_

#include <kxm/Vectoid/Camera.h>

namespace kxm {
namespace Vectoid {
namespace Metal {

//! This scene graph node represents a camera.
/*! 
 *  \ingroup VectoidMetal
 */ 
class Camera : public Vectoid::Camera {
  public:
    Camera();
    Camera(const Camera &other) = delete;
    Camera &operator=(const Camera &other) = delete;
    void Render();
};

}    // Namespace Metal.
}    // Namespace Vectoid.
}    // Namespace kxm.

#endif    // KXM_VECTOID_METAL_CAMERA_H_
