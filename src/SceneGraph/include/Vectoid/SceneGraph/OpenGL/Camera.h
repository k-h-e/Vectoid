#ifndef VECTOID_SCENEGRAPH_OPENGL_CAMERA_H_
#define VECTOID_SCENEGRAPH_OPENGL_CAMERA_H_

#include <Vectoid/SceneGraph/Camera.h>

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

class Context;
class RenderTarget;

//! This scene graph node represents a camera.
class Camera : public Vectoid::SceneGraph::Camera {
  public:
    Camera()                               = delete;
    Camera(const std::shared_ptr<Context> &context);
    Camera(const Camera &other)            = delete;
    Camera &operator=(const Camera &other) = delete;
    Camera(Camera &&other)                 = delete;
    Camera &operator=(Camera &&other)      = delete;

    void RenderPre() override;
};

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_OPENGL_CAMERA_H_
