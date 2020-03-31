#include <Vectoid/DataSet/VertexSet.h>

using Vectoid::Core::Vector;

namespace Vectoid {
namespace DataSet {

VertexSet::VertexSet() {
    // Nop.
}

int VertexSet::Count() {
    return static_cast<int>(vertices_.size());
}

int VertexSet::Add(const Core::Vector<float> &vertex) {
    auto iterator = vertexToIdMap_.find(vertex);
    if (iterator != vertexToIdMap_.end()) {
        return iterator->second;
    }
    else {
        int id = static_cast<int>(vertices_.size());
        vertices_.push_back(vertex);
        vertexToIdMap_[vertex] = id;
        return id;
    }
}

const Vector<float> &VertexSet::operator[](int index) {
    assert((index >= 0) && (index < static_cast<int>(vertices_.size())));
    return vertices_[index];
}

}    // Namespace DataSet.
}    // Namespace Vectoid.
