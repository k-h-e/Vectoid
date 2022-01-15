#include <Vectoid/SceneGraph/OpenGL/PerspectiveProjection.h>

#include <Vectoid/SceneGraph/OpenGL/Context.h>
#include <Vectoid/SceneGraph/OpenGL/OpenGL.h>

using std::shared_ptr;

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

PerspectiveProjection::PerspectiveProjection(const shared_ptr<Context> &context)
        : SceneGraph::PerspectiveProjection(context) {
    // Nop.
}

void PerspectiveProjection::RenderPre() {
    if (parametersChanged_) {
        float windowWidth, windowHeight;
        GetWindowDimensions(&windowWidth, &windowHeight);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
#ifdef KXM_VECTOID_GLES
        glFrustumf(-windowWidth  / 2.0f, windowWidth  / 2.0f,
                   -windowHeight / 2.0f, windowHeight / 2.0f,
                    eyepointDistance_, eyepointDistance_ + viewingDepth_);
#else
        glFrustum(-windowWidth  / 2.0f, windowWidth  / 2.0f,
                  -windowHeight / 2.0f, windowHeight / 2.0f,
                   eyepointDistance_, eyepointDistance_ + viewingDepth_);
#endif
        glTranslatef(0.0, 0.0, -eyepointDistance_);
        glMatrixMode(GL_MODELVIEW);
        parametersChanged_ = false;
    }
}

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.
