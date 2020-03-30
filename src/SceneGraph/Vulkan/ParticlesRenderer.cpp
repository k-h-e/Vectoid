#include <Vectoid/SceneGraph/Vulkan/ParticlesRenderer.h>

#include <kxm/Core/logging.h>
#include <Vectoid/Core/Particles.h>

using namespace std;
using namespace kxm::Core;
using namespace kxm::Vectoid;

namespace Vectoid {
namespace SceneGraph {
namespace Vulkan {

ParticlesRenderer::ParticlesRenderer(const shared_ptr<Context> &context, const shared_ptr<Particles> &particles)
        : Vectoid::ParticlesRenderer(particles),
          context_(context) {
    // Nop.
}

void ParticlesRenderer::Render() {
    Core::Log().Stream() << "Vulkan::ParticlesRenderer::Render()" << endl;
}

}    // Namespace Vulkan.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.
