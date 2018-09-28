#ifndef KXM_VECTOID_VULKAN_AGECOLOREDPARTICLES_H_
#define KXM_VECTOID_VULKAN_AGECOLOREDPARTICLES_H_

#include <kxm/Vectoid/AgeColoredParticles.h>

namespace kxm {
namespace Vectoid {
namespace Vulkan {

class RenderTarget;
class Context;

//! Renders particles in different colors, depending of their age.
/*!
 *  \ingroup VectoidVulkan
 */
class AgeColoredParticles : public Vectoid::AgeColoredParticles {
 public:
    friend class RenderTarget;
    
    AgeColoredParticles(const AgeColoredParticles &other) = delete;
    AgeColoredParticles &operator=(const AgeColoredParticles &other) = delete;
    void Render();
    
  private:
    AgeColoredParticles(const std::shared_ptr<Context> &context, const std::shared_ptr<Vectoid::Particles> &particles);
    
    std::shared_ptr<Context> context_;
};

}    // Namespace Vulkan.
}    // Namespace Vectoid.
}    // Namespace kxm.

#endif    // KXM_VECTOID_VULKAN_AGECOLOREDPARTICLES_H_
