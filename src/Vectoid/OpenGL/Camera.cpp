#include <kxm/Vectoid/OpenGL/Camera.h>

#include <kxm/Vectoid/OpenGL/OpenGL.h>

namespace kxm {
namespace Vectoid {
namespace OpenGL {

Camera::Camera()
        : Vectoid::Camera() {
    //Nop.
}

void Camera::Render() {
    Transform<float> inverse(Transform<float>::InitAsInverse, transform_);
    glLoadIdentity();
    glMultMatrixf(inverse.MatrixElements());
    Vectoid::Camera::Render();
}

}    // Namespace OpenGL.
}    // Namespace Vectoid.
}    // Namespace kxm.
