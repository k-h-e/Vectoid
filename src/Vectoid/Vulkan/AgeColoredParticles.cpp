#include <kxm/Vectoid/Vulkan/AgeColoredParticles.h>

#include <kxm/Core/logging.h>
#include <kxm/Core/NumberTools.h>
#include <kxm/Vectoid/Particles.h>

using namespace std;
using namespace kxm::Core;

namespace kxm {
namespace Vectoid {
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
}    // Namespace Vectoid.
}    // Namespace kxm.
