#ifndef VECTOID_SCENEGRAPH_VULKAN_AGECOLOREDPARTICLES_H_
#define VECTOID_SCENEGRAPH_VULKAN_AGECOLOREDPARTICLES_H_

#include <Vectoid/SceneGraph/AgeColoredParticles.h>

namespace Vectoid {
namespace SceneGraph {
namespace Vulkan {

class RenderTarget;
class Context;

//! Renders particles in different colors, depending of their age.
class AgeColoredParticles : public Vectoid::SceneGraph::AgeColoredParticles {
 public:
    friend class RenderTarget;
    
    AgeColoredParticles(const AgeColoredParticles &other) = delete;
    AgeColoredParticles &operator=(const AgeColoredParticles &other) = delete;
    void Render();
    
  private:
    AgeColoredParticles(const std::shared_ptr<Context> &context,
                        const std::shared_ptr<Vectoid::Core::Particles> &particles);
    
    std::shared_ptr<Context> context_;
};

}    // Namespace Vulkan.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_VULKAN_AGECOLOREDPARTICLES_H_
