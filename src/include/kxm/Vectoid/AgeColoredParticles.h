#ifndef KXM_VECTOID_AGECOLOREDPARTICLES_H_
#define KXM_VECTOID_AGECOLOREDPARTICLES_H_

#include <vector>
#include <memory>
#include <kxm/Vectoid/Vector.h>
#include <kxm/Vectoid/GeometryInterface.h>

namespace kxm {
namespace Vectoid {

class Particles;

//! Renders particles in different colors, depending of their age.
/*!
 *  \ingroup Vectoid
 */
class AgeColoredParticles : public virtual GeometryInterface {
 public:
    AgeColoredParticles(const std::shared_ptr<Vectoid::Particles> &particles);
    AgeColoredParticles(const AgeColoredParticles &other) = delete;
    AgeColoredParticles &operator=(const AgeColoredParticles &other) = delete;
    
  protected:
    std::shared_ptr<Vectoid::Particles> particles_;
    float                               highAge_;
    std::vector<Vectoid::Vector>        colors_;
};

}    // Namespace Vectoid.
}    // Namespace kxm.

#endif    // KXM_VECTOID_AGECOLOREDPARTICLES_H_
