#include <Vectoid/SceneGraph/OpenGL/Geode.h>

using namespace std;

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

Geode::Geode(const shared_ptr<GeometryInterface> &geometry)
        : SceneGraph::Geode(geometry) {
    // Nop.
}

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.
