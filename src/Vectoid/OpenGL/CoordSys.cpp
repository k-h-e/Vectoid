#include <kxm/Vectoid/OpenGL/CoordSys.h>

#include <kxm/Vectoid/OpenGL/OpenGL.h>

namespace kxm {
namespace Vectoid {
namespace OpenGL {

CoordSys::CoordSys()
        : Vectoid::CoordSys() {
    // Nop.
}

void CoordSys::Render(RenderContext *context) {
    glPushMatrix();
    glMultMatrixf(transform_.MatrixElements());
    CoordSysCore::Render(context);
    glPopMatrix();
}

}    // Namespace OpenGL.
}    // Namespace Vectoid.
}    // Namespace kxm.
