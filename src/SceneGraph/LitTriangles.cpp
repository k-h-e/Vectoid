#include <Vectoid/SceneGraph/LitTriangles.h>

using std::shared_ptr;
using Vectoid::Core::Vector;
using Vectoid::Core::TriangleProviderInterface;

namespace Vectoid {
namespace SceneGraph {

LitTriangles::LitTriangles(const shared_ptr<TriangleProviderInterface> &triangleProvider)
        : triangleProvider_(triangleProvider),
          color_(.8f, .8f, .8f) {
    // Nop.
}

void LitTriangles::SetColor(const Vector<float> &color) {
    color_ = color;
}

}    // Namespace SceneGraph.
}    // Namespace Vectoid.
