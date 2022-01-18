#include <Vectoid/SceneGraph/Context.h>

namespace Vectoid {
namespace SceneGraph {

Context::Context()
        : nodes_(1) {
    // Nop.
}

int Context::RegisterNode(Node *node) {
    int nodeId;
    nodes_.Get(0, &nodeId) = node;
    return nodeId;
}

void Context::UnregisterNode(int nodeId) {
    nodes_.Put(nodeId);
}

}    // Namespace SceneGraph.
}    // Namespace Vectoid.
