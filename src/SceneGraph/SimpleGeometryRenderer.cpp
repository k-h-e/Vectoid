#include <Vectoid/SceneGraph/SimpleGeometryRenderer.h>

using namespace std;

namespace Vectoid {
namespace SceneGraph {

SimpleGeometryRenderer::SimpleGeometryRenderer(const shared_ptr<SimpleGeometry> &geometry)
        : geometry_(geometry) {
    // Nop.
}

}    // Namespace SceneGraph.
}    // Namespace Vectoid.
