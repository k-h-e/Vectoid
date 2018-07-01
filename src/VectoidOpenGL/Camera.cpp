#include <kxm/VectoidOpenGL/Camera.h>

#include <kxm/VectoidOpenGL/OpenGL.h>

namespace kxm {
namespace Vectoid {
namespace OpenGL {

void Camera::Render(RenderContext *context) {
    Transform inverse(Transform::InitAsInverse, transform_);
    glLoadIdentity();
    glMultMatrixf(inverse.MatrixElements());
    CoordSysCore::Render(context);
}

}    // Namespace OpenGL.
}    // Namespace Vectoid.
}    // Namespace kxm.
