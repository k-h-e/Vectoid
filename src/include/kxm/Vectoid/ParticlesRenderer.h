#ifndef KXM_VECTOID_PARTICLESRENDERER_H_
#define KXM_VECTOID_PARTICLESRENDERER_H_

#include <vector>
#include <memory>
#include <kxm/Vectoid/GeometryInterface.h>

namespace kxm {
namespace Vectoid {

class Particles;

//! Renders particles.
/*!
 *  \ingroup Vectoid
 */
class ParticlesRenderer : public virtual Vectoid::GeometryInterface {
  public:
    ParticlesRenderer(const ParticlesRenderer &other) = delete;
    ParticlesRenderer &operator=(const ParticlesRenderer &other) = delete;
    
  protected:
    ParticlesRenderer(const std::shared_ptr<Vectoid::Particles> &particles);
  
    std::shared_ptr<Vectoid::Particles> particles_;
};


}    // Namespace Vectoid.
}    // Namespace kxm.


#endif    // KXM_VECTOID_PARTICLESRENDERER_H_
