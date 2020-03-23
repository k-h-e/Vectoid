#include <kxm/Vectoid/OpenGL/SimpleLighting.h>

#include <kxm/Vectoid/OpenGL/OpenGL.h>

namespace kxm {
namespace Vectoid {
namespace OpenGL {

SimpleLighting::SimpleLighting() {
    // Nop.
}

void SimpleLighting::Render() {
    if (settingsChanged_)
    {
        GLfloat lightPosition[4] = { 0.0f, 0.0f, 20.0f, 1.0f };
        glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
        settingsChanged_ = false;
    }

    glEnable(GL_LIGHT0);
    Vectoid::SimpleLighting::Render();
    glDisable(GL_LIGHT0);
}

}    // Namespace OpenGL.
}    // Namespace Vectoid.
}    // Namespace kxm.
