#ifndef KXM_VECTOID_CAMERA_H_
#define KXM_VECTOID_CAMERA_H_

#include <kxm/Vectoid/CoordSysCore.h>

namespace kxm {
namespace Vectoid {

class RenderContext;

//! This scene graph node represents a camera.
/*! 
 *  \ingroup Vectoid
 */ 
class Camera : public CoordSysCore {
  public:
    Camera();
    void Render(RenderContext *context);
    
  private:
    Camera(const Camera &other);
    Camera &operator=(const Camera &other);
};

}    // Namespace Vectoid.
}    // Namespace kxm.

#endif    // KXM_VECTOID_CAMERA_H_
