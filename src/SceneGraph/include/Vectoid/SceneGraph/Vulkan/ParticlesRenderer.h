#ifndef VECTOID_SCENEGRAPH_VULKAN_PARTICLESRENDERER_H_
#define VECTOID_SCENEGRAPH_VULKAN_PARTICLESRENDERER_H_

#include <vector>
#include <Vectoid/SceneGraph/ParticlesRenderer.h>

namespace Vectoid {
namespace SceneGraph {
namespace Vulkan {

class RenderTarget;
class Context;

//! Renders particles.
/*!
 *  \ingroup VectoidVulkan
 */
class ParticlesRenderer : public Vectoid::SceneGraph::ParticlesRenderer {
  public:
    friend class RenderTarget;
    
    ParticlesRenderer(const ParticlesRenderer &other) = delete;
    ParticlesRenderer &operator=(const ParticlesRenderer &other) = delete;
    void Render();
    
  private:
    ParticlesRenderer(const std::shared_ptr<Context> &context, const std::shared_ptr<Vectoid::Particles> &particles);
    
    std::shared_ptr<Context> context_;
};

}    // Namespace Vulkan.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.


#endif    // VECTOID_SCENEGRAPH_VULKAN_PARTICLESRENDERER_H_

