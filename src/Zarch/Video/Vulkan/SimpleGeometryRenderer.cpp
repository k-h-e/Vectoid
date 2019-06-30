#include <kxm/Zarch/Video/Vulkan/SimpleGeometryRenderer.h>

#include <kxm/Core/logging.h>
#include <kxm/Zarch/SimpleGeometry.h>

using namespace std;
using namespace kxm::Vectoid;

namespace kxm {
namespace Zarch {
namespace Video {
namespace Vulkan {

SimpleGeometryRenderer::SimpleGeometryRenderer(const shared_ptr<Vectoid::Vulkan::Context> &context,
                                               const shared_ptr<SimpleGeometry> &geometry)
        : Video::SimpleGeometryRenderer(geometry),
          context_(context) {

}

void SimpleGeometryRenderer::Render() {
    Core::Log().Stream() << "Vulkan::SimpleGeometryRenderer::Render()" << endl;
}

}    // Namespace Vulkan.
}    // Namespace Video.
}    // Namespace Zarch.
}    // Namespace kxm.

