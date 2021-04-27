#include <Vectoid/SceneGraph/OpenGL/CoordSys.h>

#include <Vectoid/SceneGraph/OpenGL/OpenGL.h>

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

CoordSys::CoordSys()
        : SceneGraph::CoordSys() {
    // Nop.
}

void CoordSys::RenderPre() {
    glPushMatrix();
    glMultMatrixf(transform_.MatrixElements());
}

void CoordSys::RenderPost() {
    glPopMatrix();
}

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.
