#include <Vectoid/SceneGraph/LitTriangles.h>

using std::shared_ptr;
using Vectoid::Core::TriangleProviderInterface;

namespace Vectoid {
namespace SceneGraph {

LitTriangles::LitTriangles(const shared_ptr<TriangleProviderInterface> &triangleProvider)
        : triangleProvider_(triangleProvider) {
    // Nop.
}

}    // Namespace SceneGraph.
}    // Namespace Vectoid.
