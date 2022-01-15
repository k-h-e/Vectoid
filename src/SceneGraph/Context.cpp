#include <Vectoid/SceneGraph/Context.h>

#include <K/Core/Log.h>

using std::to_string;
using K::Core::Log;

namespace Vectoid {
namespace SceneGraph {

Context::Context()
        : nodes_(1) {
    // Nop.
}

int Context::RegisterNode(Node *node) {
    int nodeId;
    nodes_.Get(0, &nodeId) = node;
    Log::Print(Log::Level::Debug, this, [&]{
        return "scene graph node registered, num=" + to_string(nodes_.Count() - nodes_.IdleCount());
    });
    return nodeId;
}

void Context::UnregisterNode(int nodeId) {
    nodes_.Put(nodeId);
    Log::Print(Log::Level::Debug, this, [&]{
        return "scene graph node unregistered, num_remaining=" + to_string(nodes_.Count() - nodes_.IdleCount());
    });
}

}    // Namespace SceneGraph.
}    // Namespace Vectoid.
