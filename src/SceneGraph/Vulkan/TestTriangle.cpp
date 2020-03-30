#include <Vectoid/SceneGraph/Vulkan/TestTriangle.h>

#include <kxm/Core/logging.h>

using namespace std;

namespace Vectoid {
namespace SceneGraph {
namespace Vulkan {

TestTriangle::TestTriangle(const shared_ptr<Context> &context)
        : Vectoid::TestTriangle(),
          context_(context) {
    // Nop.
}

void TestTriangle::Render() {
    Core::Log().Stream() << "Vulkan::TestTriangle::Render()" << endl;
}

}    // Namespace Vulkan.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.
