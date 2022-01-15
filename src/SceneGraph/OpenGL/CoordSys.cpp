#include <Vectoid/SceneGraph/OpenGL/CoordSys.h>

#include <Vectoid/SceneGraph/OpenGL/Context.h>
#include <Vectoid/SceneGraph/OpenGL/OpenGL.h>

using std::shared_ptr;

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

CoordSys::CoordSys(const shared_ptr<Context> &context)
        : SceneGraph::CoordSys(context) {
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
