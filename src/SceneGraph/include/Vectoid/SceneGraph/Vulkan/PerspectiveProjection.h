#ifndef VECTOID_SCENEGRAPH_VULKAN_PERSPECTIVEPROJECTION_H_
#define VECTOID_SCENEGRAPH_VULKAN_PERSPECTIVEPROJECTION_H_

#include <Vectoid/SceneGraph/PerspectiveProjection.h>

#include <Vectoid/Core/FullTransform.h>

namespace Vectoid {
namespace SceneGraph {
namespace Vulkan {

class RenderTarget;
class Context;

//! Perspective screen projection, defining a frustum-shaped viewing volume.
class PerspectiveProjection : public Vectoid::SceneGraph::PerspectiveProjection {
  public:
    friend class RenderTarget;
    
    PerspectiveProjection(const PerspectiveProjection &other)            = delete;
    PerspectiveProjection &operator=(const PerspectiveProjection &other) = delete;
    PerspectiveProjection(PerspectiveProjection &&other)                 = delete;
    PerspectiveProjection &operator=(PerspectiveProjection &&other)      = delete;
    
    void RenderPre() override;
    void RenderPost() override;
    
  private:
    PerspectiveProjection(const std::shared_ptr<Context> &context);
    
    std::shared_ptr<Context> context_;
    Core::FullTransform transform_;
    Core::FullTransform objectTransformBackup_;
};

}    // Namespace Vulkan.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_VULKAN_PERSPECTIVEPROJECTION_H_
