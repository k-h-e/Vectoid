#include <Vectoid/SceneGraph/Points.h>

using std::shared_ptr;

namespace Vectoid {
namespace SceneGraph {

Points::Points(const shared_ptr<Context> &context, const shared_ptr<DataSet::Points> &points)
        : Geometry(context),
          points_(points),
          color_(.8f, .8f, .8f) {
    // Nop.
}

void Points::SetColor(const Core::Vector<float> &color) {
    color_ = color;
}

}    // Namespace SceneGraph.
}    // Namespace Vectoid.
