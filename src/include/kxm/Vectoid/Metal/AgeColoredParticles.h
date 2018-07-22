#ifndef KXM_VECTOID_METAL_AGECOLOREDPARTICLES_H_
#define KXM_VECTOID_METAL_AGECOLOREDPARTICLES_H_

#include <kxm/Vectoid/AgeColoredParticles.h>

namespace kxm {
namespace Vectoid {
namespace Metal {

//! Renders particles in different colors, depending of their age.
/*!
 *  \ingroup VectoidMetal
 */
class AgeColoredParticles : public Vectoid::AgeColoredParticles {
 public:
    AgeColoredParticles(std::shared_ptr<Vectoid::Particles> particles);
    AgeColoredParticles(const AgeColoredParticles &other) = delete;
    AgeColoredParticles &operator=(const AgeColoredParticles &other) = delete;
    void Render();
};

}    // Namespace Metal.
}    // Namespace Vectoid.
}    // Namespace kxm.

#endif    // KXM_VECTOID_METAL_AGECOLOREDPARTICLES_H_
