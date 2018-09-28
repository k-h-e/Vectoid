#ifndef KXM_VECTOID_METAL_CAMERA_H_
#define KXM_VECTOID_METAL_CAMERA_H_

#include <kxm/Vectoid/Camera.h>

namespace kxm {
namespace Vectoid {
namespace Metal {

class RenderTarget;
class Context;

//! This scene graph node represents a camera.
/*! 
 *  \ingroup VectoidMetal
 */ 
class Camera : public Vectoid::Camera {
  public:
    friend class RenderTarget;
    
    Camera(const Camera &other) = delete;
    Camera &operator=(const Camera &other) = delete;
    void Render();
    
  private:
    Camera(const std::shared_ptr<Context> &context);
  
    std::shared_ptr<Context> context_;
};

}    // Namespace Metal.
}    // Namespace Vectoid.
}    // Namespace kxm.

#endif    // KXM_VECTOID_METAL_CAMERA_H_
