#include <kxm/Vectoid/Camera.h>

#include <kxm/Vectoid/OpenGL.h>

namespace kxm {
namespace Vectoid {

Camera::Camera() {
}

void Camera::Render(RenderContext *context) {
    Transform inverse(Transform::InitAsInverse, transform_);
    glLoadIdentity();
    glMultMatrixf(inverse.MatrixElements());
    CoordSysCore::Render(context);
}

}    // Namespace Vectoid.
}    // Namespace kxm.
