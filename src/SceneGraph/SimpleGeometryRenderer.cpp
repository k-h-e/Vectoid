#include <Vectoid/SceneGraph/SimpleGeometryRenderer.h>

using namespace std;

namespace Vectoid {
namespace SceneGraph {

SimpleGeometryRenderer::SimpleGeometryRenderer(const shared_ptr<Context> &context,
                                               const shared_ptr<SimpleGeometry> &geometry)
        : Geometry(context),
          geometry_(geometry) {
    // Nop.
}

}    // Namespace SceneGraph.
}    // Namespace Vectoid.
