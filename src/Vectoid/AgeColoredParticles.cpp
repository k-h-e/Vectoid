#include <kxm/Vectoid/AgeColoredParticles.h>

namespace kxm {
namespace Vectoid {

using std::shared_ptr;

AgeColoredParticles::AgeColoredParticles(shared_ptr<Vectoid::Particles> particles)
        : particles_(particles),
          highAge_(1.5f) {
    colors_.push_back(Vector(1.0f, 1.0f, 1.0f));
    colors_.push_back(Vector(1.0f, 1.0f, 0.0f));
    colors_.push_back(Vector(1.0f, 0.0f, 0.0f));
    colors_.push_back(Vector( .3f, 0.0f, 0.0f));
    
    // There must be at least two colors!
}

}    // Namespace Vectoid.
}    // Namespace kxm.
