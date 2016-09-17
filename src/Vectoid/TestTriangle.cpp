#include <kxm/Vectoid/TestTriangle.h>

namespace kxm {
namespace Vectoid {

const GLfloat TestTriangle::vertices[9] = { -1.0f, 0.0f, 0.0f,
                                             1.0f, 0.0f, 0.0f,
                                             0.0f, 1.0f, 0.0f  };

TestTriangle::TestTriangle() {
}

void TestTriangle::Render(RenderContext *context) {
    glColor4f(.8f, .8f, .2f, 1.0f);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
   	glEnableClientState(GL_VERTEX_ARRAY);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableClientState(GL_VERTEX_ARRAY);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}

}    // Namespace Vectoid.
}    // Namespace kxm.
