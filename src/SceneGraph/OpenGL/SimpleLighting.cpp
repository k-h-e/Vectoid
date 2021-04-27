#include <Vectoid/SceneGraph/OpenGL/SimpleLighting.h>

#include <Vectoid/SceneGraph/OpenGL/OpenGL.h>

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

SimpleLighting::SimpleLighting() {
    // Nop.
}

void SimpleLighting::RenderPre() {
    GLfloat lightPosition[4] = { 0.0f, 0.0f, 20.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.
