#include <Vectoid/SceneGraph/Vulkan/AgeColoredParticles.h>

#include <K/Core/Log.h>
#include <K/Core/NumberTools.h>
#include <Vectoid/Core/Particles.h>

using namespace std;
using K::Core::Log;

namespace Vectoid {
namespace SceneGraph {
namespace Vulkan {

AgeColoredParticles::AgeColoredParticles(const shared_ptr<Context> &context,
                                         const shared_ptr<Core::Particles> &particles)
        : Vectoid::SceneGraph::AgeColoredParticles(particles),
          context_(context) {
    // Nop.
}
    
void AgeColoredParticles::Render() {
    Log::Print(Log::Level::Debug, this, []{ return "Vulkan::AgeColoredParticles::Render()"; });
}

}    // Namespace Vulkan.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.
