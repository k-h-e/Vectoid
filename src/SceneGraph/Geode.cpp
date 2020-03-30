#include <Vectoid/SceneGraph/Geode.h>

#include <cassert>

using namespace std;

namespace Vectoid {
namespace SceneGraph {

Geode::Geode(const shared_ptr<GeometryInterface> &geometry) {
    assert(!!geometry);
    geometry_ = geometry;
}

void Geode::Render() {
    geometry_->Render();
    SceneGraphNode::Render();
}

}    // Namespace SceneGraph.
}    // Namespace Vectoid.
