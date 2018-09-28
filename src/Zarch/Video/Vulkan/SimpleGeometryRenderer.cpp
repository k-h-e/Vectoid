#include <kxm/Zarch/Video/Vulkan/SimpleGeometryRenderer.h>

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
    
}

}    // Namespace Vulkan.
}    // Namespace Video.
}    // Namespace Zarch.
}    // Namespace kxm.

