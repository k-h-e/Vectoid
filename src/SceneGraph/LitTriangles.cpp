#include <Vectoid/SceneGraph/LitTriangles.h>

using std::shared_ptr;
using Vectoid::Core::Vector;
using Vectoid::Core::TriangleProviderInterface;

namespace Vectoid {
namespace SceneGraph {

LitTriangles::LitTriangles(const shared_ptr<Context> &context,
                           const shared_ptr<TriangleProviderInterface> &triangleProvider)
        : Geometry{context},
          triangleProvider_{triangleProvider},
          color_{.8f, .8f, .8f},
          lightingEnabled_{true},
          depthTestEnabled_{true} {
    // Nop.
}

void LitTriangles::SetColor(const Vector<float> &color) {
    color_ = color;
}

void LitTriangles::EnableLighting(bool enabled) {
    lightingEnabled_ = enabled;
}

void LitTriangles::EnableDepthTest(bool enabled) {
    depthTestEnabled_ = enabled;
}

}    // Namespace SceneGraph.
}    // Namespace Vectoid.
