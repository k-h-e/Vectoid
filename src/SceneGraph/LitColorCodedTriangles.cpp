#include <Vectoid/SceneGraph/LitColorCodedTriangles.h>

using std::function;
using std::shared_ptr;
using std::vector;
using Vectoid::Core::ExtendedTriangleProviderInterface;
using Vectoid::Core::TriangleProviderInterface;
using Vectoid::Core::Vector;

namespace Vectoid {
namespace SceneGraph {

LitColorCodedTriangles::LitColorCodedTriangles(const shared_ptr<Context> &context,
                                               const shared_ptr<TriangleProviderInterface> &triangleProvider)
        : Geometry(context),
          triangleProvider_(triangleProvider) {
    // Nop.
}

void LitColorCodedTriangles::SetColorCodingFunction(
        const function<Vector<float>(const Vector<float> &)> &colorCodingFunction) {
    colorCodingFunction_ = colorCodingFunction;
}

void LitColorCodedTriangles::EnableGouraudShading(
        const shared_ptr<ExtendedTriangleProviderInterface> &triangleProvider) {
    gouraudTriangleProvider_ = triangleProvider;
}

void LitColorCodedTriangles::DisableGouraudShading() {
    gouraudTriangleProvider_.reset();
}

}    // Namespace SceneGraph.
}    // Namespace Vectoid.
