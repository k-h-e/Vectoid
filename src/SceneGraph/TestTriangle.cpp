#include <Vectoid/SceneGraph/TestTriangle.h>

using std::shared_ptr;

namespace Vectoid {
namespace SceneGraph {

TestTriangle::TestTriangle(const shared_ptr<Context> &context)
        : Geometry(context) {
    // Nop.
}

}    // Namespace SceneGraph.
}    // Namespace Vectoid.
