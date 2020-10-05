#ifndef VECTOID_SCENEGRAPH_VULKAN_CAMERA_H_
#define VECTOID_SCENEGRAPH_VULKAN_CAMERA_H_

#include <Vectoid/SceneGraph/Camera.h>

namespace Vectoid {
namespace SceneGraph {
namespace Vulkan {

class RenderTarget;
class Context;

//! This scene graph node represents a camera.
class Camera : public Vectoid::SceneGraph::Camera {
  public:
    friend class RenderTarget;
    
    Camera(const Camera &other) = delete;
    Camera &operator=(const Camera &other) = delete;
    void Render();
    
  private:
    Camera(const std::shared_ptr<Context> &context);
    
    std::shared_ptr<Context> context_;
};

}    // Namespace Vulkan.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_VULKAN_CAMERA_H_
