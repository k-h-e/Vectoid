#include <kxm/Vectoid/Vulkan/TestTriangle.h>

using namespace std;

namespace kxm {
namespace Vectoid {
namespace Vulkan {

TestTriangle::TestTriangle(const shared_ptr<Context> &context)
        : Vectoid::TestTriangle(),
          context_(context) {
    // Nop.
}

void TestTriangle::Render() {
}

}    // Namespace Vulkan.
}    // Namespace Vectoid.
}    // Namespace kxm.
