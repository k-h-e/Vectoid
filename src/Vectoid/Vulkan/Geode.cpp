#include <kxm/Vectoid/Vulkan/Geode.h>

#include <kxm/Core/logging.h>

using namespace std;

namespace kxm {
namespace Vectoid {
namespace Vulkan {

Geode::Geode(const shared_ptr<GeometryInterface> &geometry)
        : Vectoid::Geode(geometry) {
    // Nop.
}

void Geode::Render() {
    Core::Log().Stream() << "Vulkan::Geode::Render()" << endl;
    Vectoid::Geode::Render();
}

}    // Namespace Vulkan.
}    // Namespace Vectoid.
}    // Namespace kxm.
