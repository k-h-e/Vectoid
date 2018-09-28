#include <kxm/Vectoid/Vulkan/CoordSys.h>

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
}

}    // Namespace Vulkan.
}    // Namespace Vectoid.
}    // Namespace kxm.
