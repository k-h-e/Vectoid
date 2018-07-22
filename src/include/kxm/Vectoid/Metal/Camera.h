#ifndef KXM_VECTOID_METAL_CAMERA_H_
#define KXM_VECTOID_METAL_CAMERA_H_

#include <kxm/Vectoid/Camera.h>

namespace kxm {
namespace Vectoid {
namespace Metal {

class Context;

//! This scene graph node represents a camera.
/*! 
 *  \ingroup VectoidMetal
 */ 
class Camera : public Vectoid::Camera {
  public:
    Camera(const std::shared_ptr<Context> &context);
    Camera(const Camera &other) = delete;
    Camera &operator=(const Camera &other) = delete;
    void Render();
    
  private:
    std::shared_ptr<Context> context_;
};

}    // Namespace Metal.
}    // Namespace Vectoid.
}    // Namespace kxm.

#endif    // KXM_VECTOID_METAL_CAMERA_H_
