#include <Vectoid/SceneGraph/AgeColoredParticles.h>

using Vectoid::Core::Vector;
using Vectoid::Core::Particles;

namespace Vectoid {
namespace SceneGraph {

using std::shared_ptr;

AgeColoredParticles::AgeColoredParticles(const shared_ptr<Particles> &particles)
        : particles_(particles),
          highAge_(1.5f) {
    colors_.push_back(Vector<float>(1.0f, 1.0f, 1.0f));
    colors_.push_back(Vector<float>(1.0f, 1.0f, 0.0f));
    colors_.push_back(Vector<float>(1.0f, 0.0f, 0.0f));
    colors_.push_back(Vector<float>( .3f, 0.0f, 0.0f));
    
    // There must be at least two colors!
}

}    // Namespace SceneGraph.
}    // Namespace Vectoid.
