#include <Vectoid/DataSet/DelauneyTriangulation.h>

using Vectoid::Core::Vector;

namespace Vectoid {
namespace DataSet {

DelauneyTriangulation::DelauneyTriangulation()
        : vertexSet_(new VertexSet()) {
    // Nop.
}

void DelauneyTriangulation::Add(const Vector<float> &point) {
    vertexSet_->Add(Vector<float>(point.x, point.y, 0.0f));
}

bool DelauneyTriangulation::Compute() {
    return false;
}

}    // Namespace DataSet.
}    // Namespace Vectoid.

