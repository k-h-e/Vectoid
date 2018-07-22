#ifndef KXM_VECTOID_METAL_PARTICLESRENDERER_H_
#define KXM_VECTOID_METAL_PARTICLESRENDERER_H_

#include <kxm/Vectoid/ParticlesRenderer.h>

#include <vector>

namespace kxm {
namespace Vectoid {
namespace Metal {

class Context;

//! Renders particles.
/*!
 *  \ingroup VectoidMetal
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

}    // Namespace Metal.
}    // Namespace Vectoid.
}    // Namespace kxm.


#endif    // KXM_VECTOID_METAL_PARTICLESRENDERER_H_

