#include <Vectoid/SceneGraph/RenderVisitor.h>

#include <Vectoid/SceneGraph/Node.h>

using std::shared_ptr;

namespace Vectoid {
namespace SceneGraph {
    
void RenderVisitor::Visit(const shared_ptr<Node> &node) {
    node->RenderPre();
}

void RenderVisitor::Leave(const shared_ptr<Node> &node) {
    node->RenderPost();
}

}    // Namespace SceneGraph.
}    // Namespace Vectoid.
