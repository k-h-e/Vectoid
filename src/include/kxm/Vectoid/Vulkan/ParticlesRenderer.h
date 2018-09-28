#ifndef KXM_VECTOID_VULKAN_PARTICLESRENDERER_H_
#define KXM_VECTOID_VULKAN_PARTICLESRENDERER_H_

#include <vector>
#include <kxm/Vectoid/ParticlesRenderer.h>

namespace kxm {
namespace Vectoid {
namespace Vulkan {

class Context;

//! Renders particles.
/*!
 *  \ingroup VectoidVulkan
 */
class ParticlesRenderer : public Vectoid::ParticlesRenderer {
  public:
    ParticlesRenderer(const std::shared_ptr<Context> &context, const std::shared_ptr<Vectoid::Particles> &particles);
    ParticlesRenderer(const ParticlesRenderer &other) = delete;
    ParticlesRenderer &operator=(const ParticlesRenderer &other) = delete;
    void Render();
    
  private:
    std::shared_ptr<Context> context_;
};

}    // Namespace Vulkan.
}    // Namespace Vectoid.
}    // Namespace kxm.


#endif    // KXM_VECTOID_VULKAN_PARTICLESRENDERER_H_

