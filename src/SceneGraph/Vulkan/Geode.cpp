#include <Vectoid/SceneGraph/Vulkan/Geode.h>

#include <K/Core/Log.h>

using namespace std;
using K::Core::Log;

namespace Vectoid {
namespace SceneGraph {
namespace Vulkan {

Geode::Geode(const shared_ptr<GeometryInterface> &geometry)
        : Vectoid::SceneGraph::Geode(geometry) {
    // Nop.
}

void Geode::Render() {
    Log::Print(Log::Level::Debug, this, []{ return "Vulkan::Geode::Render()"; });
    Vectoid::SceneGraph::Geode::Render();
}

}    // Namespace Vulkan.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.
