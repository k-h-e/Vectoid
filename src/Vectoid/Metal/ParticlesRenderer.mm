#include <kxm/Vectoid/Metal/ParticlesRenderer.h>

#include <kxm/Vectoid/Particles.h>

using namespace std;
using namespace kxm::Core;
using namespace kxm::Vectoid;

namespace kxm {
namespace Vectoid {
namespace Metal {

ParticlesRenderer::ParticlesRenderer(const shared_ptr<Context> &context, const shared_ptr<Particles> &particles)
        : Vectoid::ParticlesRenderer(particles),
          context_(context) {
    // Nop.
}

void ParticlesRenderer::Render() {
}

}    // Namespace Metal.
}    // Namespace Vectoid.
}    // Namespace kxm.
