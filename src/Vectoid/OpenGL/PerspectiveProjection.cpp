#include <kxm/Vectoid/OpenGL/PerspectiveProjection.h>

#include <kxm/Vectoid/OpenGL/OpenGL.h>

namespace kxm {
namespace Vectoid {
namespace OpenGL {

PerspectiveProjection::PerspectiveProjection() {
    // Nop.
}

void PerspectiveProjection::Render() {
    if (parametersChanged_) {
        float windowWidth, windowHeight;
        ComputeWindowDimensions(&windowWidth, &windowHeight);
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
    SceneGraphNode::Render();
}

}    // Namespace OpenGL.
}    // Namespace Vectoid.
}    // Namespace kxm.
