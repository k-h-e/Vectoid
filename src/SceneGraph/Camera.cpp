#include <Vectoid/SceneGraph/Camera.h>

#include <Vectoid/SceneGraph/VisitorInterface.h>

namespace Vectoid {
namespace SceneGraph {

void Camera::Visit(VisitorInterface *visitor) {
    visitor->Visit(this);
    CoordSysCore::Visit(visitor);
    visitor->Leave(this);
}

}    // Namespace SceneGraph.
}    // Namespace Vectoid.
