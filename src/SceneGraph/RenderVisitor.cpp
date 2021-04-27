#include <Vectoid/SceneGraph/RenderVisitor.h>

#include <Vectoid/SceneGraph/Node.h>

namespace Vectoid {
namespace SceneGraph {
    
void RenderVisitor::Visit(Node *node) {
    node->RenderPre();
}

void RenderVisitor::Leave(Node *node) {
    node->RenderPost();
}

}    // Namespace SceneGraph.
}    // Namespace Vectoid.
