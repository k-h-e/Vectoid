#include <kxm/Vectoid/Metal/ParticlesRenderer.h>

#include <kxm/Vectoid/Particles.h>

using namespace std;
using namespace kxm::Core;
using namespace kxm::Vectoid;

namespace kxm {
namespace Vectoid {
namespace Metal {

ParticlesRenderer::ParticlesRenderer(shared_ptr<Particles> particles)
        : Vectoid::ParticlesRenderer(particles) {
    // Nop.
}

void ParticlesRenderer::Render() {
}

}    // Namespace Metal.
}    // Namespace Vectoid.
}    // Namespace kxm.
