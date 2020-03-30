#include <Vectoid/SceneGraph/Vulkan/AgeColoredParticles.h>

#include <kxm/Core/logging.h>
#include <kxm/Core/NumberTools.h>
#include <Vectoid/Core/Particles.h>

using namespace std;
using namespace kxm::Core;

namespace Vectoid {
namespace SceneGraph {
namespace Vulkan {

AgeColoredParticles::AgeColoredParticles(const shared_ptr<Context> &context,
                                         const shared_ptr<Vectoid::Particles> &particles)
        : Vectoid::AgeColoredParticles(particles),
          context_(context) {
    // Nop.
}
    
void AgeColoredParticles::Render() {
    Core::Log().Stream() << "Vulkan::AgeColoredParticles::Render()" << endl;
}

}    // Namespace Vulkan.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.
