#include <kxm/Vectoid/Vulkan/ParticlesRenderer.h>

#include <kxm/Vectoid/Particles.h>

using namespace std;
using namespace kxm::Core;
using namespace kxm::Vectoid;

namespace kxm {
namespace Vectoid {
namespace Vulkan {

ParticlesRenderer::ParticlesRenderer(const shared_ptr<Context> &context, const shared_ptr<Particles> &particles)
        : Vectoid::ParticlesRenderer(particles),
          context_(context) {
    // Nop.
}

void ParticlesRenderer::Render() {
}

}    // Namespace Vulkan.
}    // Namespace Vectoid.
}    // Namespace kxm.