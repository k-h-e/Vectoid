#ifndef VECTOID_SCENEGRAPH_CAMERA_H_
#define VECTOID_SCENEGRAPH_CAMERA_H_

#include <Vectoid/SceneGraph/CoordSysCore.h>

namespace Vectoid {
namespace SceneGraph {

//! This scene graph node represents a camera.
/*! 
 *  \ingroup Vectoid
 */ 
class Camera : public CoordSysCore {
  public:
    Camera(const Camera &other) = delete;
    Camera &operator=(const Camera &other) = delete;
    
  protected:
    Camera() {}
};

}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_CAMERA_H_
