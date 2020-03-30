#include <Vectoid/SceneGraph/OpenGL/CoordSys.h>

#include <Vectoid/SceneGraph/OpenGL/OpenGL.h>

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

CoordSys::CoordSys()
        : SceneGraph::CoordSys() {
    // Nop.
}

void CoordSys::Render() {
    glPushMatrix();
    glMultMatrixf(transform_.MatrixElements());
    SceneGraph::CoordSys::Render();
    glPopMatrix();
}

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.
