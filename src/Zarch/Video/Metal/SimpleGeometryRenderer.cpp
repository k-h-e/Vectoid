#include <kxm/Zarch/Video/Metal/SimpleGeometryRenderer.h>

#include <kxm/Zarch/SimpleGeometry.h>

using namespace std;
using namespace kxm::Vectoid;

namespace kxm {
namespace Zarch {
namespace Video {
namespace Metal {

SimpleGeometryRenderer::SimpleGeometryRenderer(const shared_ptr<SimpleGeometry> &geometry)
        : Video::SimpleGeometryRenderer(geometry) {

}

void SimpleGeometryRenderer::Render() {
    
}

}    // Namespace Metal.
}    // Namespace Video.
}    // Namespace Zarch.
}    // Namespace kxm.

