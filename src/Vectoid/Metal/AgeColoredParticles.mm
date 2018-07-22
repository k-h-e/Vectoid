#include <kxm/Vectoid/Metal/AgeColoredParticles.h>

#include <kxm/Core/logging.h>
#include <kxm/Core/NumberTools.h>
#include <kxm/Vectoid/Particles.h>
#include <kxm/Vectoid/OpenGL/OpenGL.h>

using namespace std;
using namespace kxm::Core;

namespace kxm {
namespace Vectoid {
namespace Metal {

AgeColoredParticles::AgeColoredParticles(const shared_ptr<Context> &context,
                                         const shared_ptr<Vectoid::Particles> &particles)
        : Vectoid::AgeColoredParticles(particles),
          context_(context) {
    // Nop.
}
    
void AgeColoredParticles::Render() {
}

}    // Namespace Metal.
}    // Namespace Vectoid.
}    // Namespace kxm.
