#ifndef KXM_VECTOID_VULKAN_AGECOLOREDPARTICLES_H_
#define KXM_VECTOID_VULKAN_AGECOLOREDPARTICLES_H_

#include <kxm/Vectoid/AgeColoredParticles.h>

namespace kxm {
namespace Vectoid {
namespace Vulkan {

class Context;

//! Renders particles in different colors, depending of their age.
/*!
 *  \ingroup VectoidVulkan
 */
class AgeColoredParticles : public Vectoid::AgeColoredParticles {
 public:
    AgeColoredParticles(const std::shared_ptr<Context> &context, const std::shared_ptr<Vectoid::Particles> &particles);
    AgeColoredParticles(const AgeColoredParticles &other) = delete;
    AgeColoredParticles &operator=(const AgeColoredParticles &other) = delete;
    void Render();
    
  private:
    std::shared_ptr<Context> context_;
};

}    // Namespace Vulkan.
}    // Namespace Vectoid.
}    // Namespace kxm.

#endif    // KXM_VECTOID_VULKAN_AGECOLOREDPARTICLES_H_
