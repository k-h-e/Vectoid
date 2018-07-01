#include <kxm/VectoidOpenGL/CoordSys.h>

#include <kxm/VectoidOpenGL/OpenGL.h>

namespace kxm {
namespace Vectoid {
namespace OpenGL {

void CoordSys::Render(RenderContext *context) {
    glPushMatrix();
    glMultMatrixf(transform_.MatrixElements());
    CoordSysCore::Render(context);
    glPopMatrix();
}

}    // Namespace OpenGL.
}    // Namespace Vectoid.
}    // Namespace kxm.
