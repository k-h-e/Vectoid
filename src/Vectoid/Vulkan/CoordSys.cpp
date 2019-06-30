#include <kxm/Vectoid/Vulkan/CoordSys.h>

#include <kxm/Core/logging.h>

using namespace std;

namespace kxm {
namespace Vectoid {
namespace Vulkan {

CoordSys::CoordSys(const shared_ptr<Context> &context)
        : Vectoid::CoordSys(),
          context_(context) {
    // Nop.
}

void CoordSys::Render() {
    Core::Log().Stream() << "Vulkan::CoordSys::Render()" << endl;
    Vectoid::CoordSys::Render();
}

}    // Namespace Vulkan.
}    // Namespace Vectoid.
}    // Namespace kxm.
