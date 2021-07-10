#include <Vectoid/SceneGraph/LitColorCodedTriangles.h>

using std::function;
using std::shared_ptr;
using Vectoid::Core::Vector;
using Vectoid::Core::TriangleProviderInterface;

namespace Vectoid {
namespace SceneGraph {

LitColorCodedTriangles::LitColorCodedTriangles(const shared_ptr<TriangleProviderInterface> &triangleProvider)
        : triangleProvider_(triangleProvider) {
    // Nop.
}

void LitColorCodedTriangles::SetColorCodingFunction(
        const function<Vector<float>(const Vector<float> &)> &colorCodingFunction) {
    colorCodingFunction_ = colorCodingFunction;
}

}    // Namespace SceneGraph.
}    // Namespace Vectoid.
