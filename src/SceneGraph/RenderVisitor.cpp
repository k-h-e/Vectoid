#include <Vectoid/SceneGraph/RenderVisitor.h>

#include <Vectoid/SceneGraph/TreeNode.h>

using std::shared_ptr;

namespace Vectoid {
namespace SceneGraph {
    
void RenderVisitor::Visit(const shared_ptr<TreeNode> &node) {
    node->RenderPre();
}

void RenderVisitor::Leave(const shared_ptr<TreeNode> &node) {
    node->RenderPost();
}

}    // Namespace SceneGraph.
}    // Namespace Vectoid.
