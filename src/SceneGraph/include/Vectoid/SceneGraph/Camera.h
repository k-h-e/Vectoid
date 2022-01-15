#ifndef VECTOID_SCENEGRAPH_CAMERA_H_
#define VECTOID_SCENEGRAPH_CAMERA_H_

#include <Vectoid/SceneGraph/CoordSysCore.h>

namespace Vectoid {
namespace SceneGraph {

//! This scene graph node represents a camera.
class Camera : public CoordSysCore {
  public:
    Camera()                               = delete;
    Camera(const Camera &other)            = delete;
    Camera &operator=(const Camera &other) = delete;
    Camera(Camera &&other)                 = delete;
    Camera &operator=(Camera &&other)      = delete;

  protected:
    Camera(const std::shared_ptr<Context> &context);
};

}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_CAMERA_H_
