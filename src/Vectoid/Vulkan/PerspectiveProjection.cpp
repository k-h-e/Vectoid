#include <kxm/Vectoid/Vulkan/PerspectiveProjection.h>

#include <kxm/Core/logging.h>

using namespace std;

namespace kxm {
namespace Vectoid {
namespace Vulkan {

PerspectiveProjection::PerspectiveProjection(const shared_ptr<Context> &context)
    : context_(context) {
    // Nop.
}

void PerspectiveProjection::Render() {
    Core::Log().Stream() << "Vulkan::PerspectiveProjection::Render()" << endl;
    Vectoid::PerspectiveProjection::Render();
}

}    // Namespace Vulkan.
}    // Namespace Vectoid.
}    // Namespace kxm.
