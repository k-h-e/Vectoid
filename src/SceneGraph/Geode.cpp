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

void Geode::SetGeometry(const std::shared_ptr<GeometryInterface> &geometry) {
    assert(!!geometry);
    geometry_ = geometry;
}

void Geode::RenderPre() {
    geometry_->Render();
}

}    // Namespace SceneGraph.
}    // Namespace Vectoid.
