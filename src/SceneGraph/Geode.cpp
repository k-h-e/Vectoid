#include <Vectoid/SceneGraph/Geode.h>

#include <cassert>
#include <Vectoid/SceneGraph/VisitorInterface.h>

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

void Geode::Visit(VisitorInterface *visitor) {
    visitor->Visit(this);
    SceneGraphNode::Visit(visitor);
    visitor->Leave(this);
}

}    // Namespace SceneGraph.
}    // Namespace Vectoid.
