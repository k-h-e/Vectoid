#include <Vectoid/SceneGraph/Points.h>

using std::shared_ptr;
using Vectoid::DataSet::VertexSet;

namespace Vectoid {
namespace SceneGraph {

Points::Points(const shared_ptr<VertexSet> &points)
        : points_(points),
          color_(.8f, .8f, .8f) {
    // Nop.
}

void Points::SetColor(const Core::Vector<float> &color) {
    color_ = color;
}

}    // Namespace SceneGraph.
}    // Namespace Vectoid.
