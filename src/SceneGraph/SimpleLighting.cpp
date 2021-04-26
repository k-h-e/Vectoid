#include <Vectoid/SceneGraph/SimpleLighting.h>

#include <Vectoid/SceneGraph/VisitorInterface.h>

namespace Vectoid {
namespace SceneGraph {

SimpleLighting::SimpleLighting() {
    // Nop.
}

void SimpleLighting::Visit(VisitorInterface *visitor) {
    visitor->Visit(this);
    SceneGraphNode::Visit(visitor);
    visitor->Leave(this);
}

}    // Namespace SceneGraph.
}    // Namespace Vectoid.
