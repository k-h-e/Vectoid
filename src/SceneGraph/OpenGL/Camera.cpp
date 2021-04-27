#include <Vectoid/SceneGraph/OpenGL/Camera.h>

#include <Vectoid/SceneGraph/OpenGL/OpenGL.h>

using Vectoid::Core::Transform;

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

Camera::Camera()
        : SceneGraph::Camera() {
    //Nop.
}

void Camera::RenderPre() {
    Transform<float> inverse(Transform<float>::InitAsInverse, transform_);
    glLoadIdentity();
    glMultMatrixf(inverse.MatrixElements());
}

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.
