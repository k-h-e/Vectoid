#include <Vectoid/SceneGraph/SimpleLighting.h>

using std::shared_ptr;

namespace Vectoid {
namespace SceneGraph {

SimpleLighting::SimpleLighting(const shared_ptr<Context> &context)
        : TreeNode(context) {
    // Nop.
}

}    // Namespace SceneGraph.
}    // Namespace Vectoid.
