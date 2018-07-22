#include <kxm/Vectoid/Metal/CoordSys.h>

using namespace std;

namespace kxm {
namespace Vectoid {
namespace Metal {

CoordSys::CoordSys(const shared_ptr<Context> &context)
        : Vectoid::CoordSys(),
          context_(context) {
    // Nop.
}

void CoordSys::Render() {
}

}    // Namespace Metal.
}    // Namespace Vectoid.
}    // Namespace kxm.
