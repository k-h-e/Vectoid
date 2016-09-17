#include <kxm/Vectoid/Geode.h>

#include <cassert>

using namespace std;

namespace kxm {
namespace Vectoid {

Geode::Geode(const shared_ptr<GeometryInterface> &geometry) {
    assert(!!geometry);
    geometry_ = geometry;
}

void Geode::Render(RenderContext *context) {
    geometry_->Render(context);
    SceneGraphNode::Render(context);
}

}    // Namespace Vectoid.
}    // Namespace kxm.
