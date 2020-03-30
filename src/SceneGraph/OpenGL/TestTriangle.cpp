#include <Vectoid/SceneGraph/OpenGL/TestTriangle.h>

#include <Vectoid/SceneGraph/OpenGL/OpenGL.h>

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

const GLfloat TestTriangle::vertices[9] = { -1.0f, 0.0f, 0.0f,
                                             1.0f, 0.0f, 0.0f,
                                             0.0f, 1.0f, 0.0f  };

TestTriangle::TestTriangle()
        : SceneGraph::TestTriangle() {
    // Nop.
}

void TestTriangle::Render() {
    glColor4f(.8f, .8f, .2f, 1.0f);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
   	glEnableClientState(GL_VERTEX_ARRAY);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableClientState(GL_VERTEX_ARRAY);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.
