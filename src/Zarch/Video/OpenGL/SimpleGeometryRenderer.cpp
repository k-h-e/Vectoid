#include <kxm/Zarch/Video/OpenGL/SimpleGeometryRenderer.h>

#include <kxm/Zarch/SimpleGeometry.h>

using namespace std;
using namespace kxm::Vectoid;

namespace kxm {
namespace Zarch {
namespace Video {
namespace OpenGL {

SimpleGeometryRenderer::SimpleGeometryRenderer(const shared_ptr<SimpleGeometry> &geometry)
        : Video::SimpleGeometryRenderer(geometry) {
    numTriangles_ = geometry->numTriangles_;
    for (float &value : geometry->vertexArray_) {
        vertexArray_.push_back(static_cast<GLfloat>(value));
    }
    for (float &value : geometry->colorArray_) {
        colorArray_.push_back(static_cast<GLfloat>(value));
    }
}

void SimpleGeometryRenderer::Render() {
    if (numTriangles_) {
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, &vertexArray_[0]);
        glColorPointer(4, GL_FLOAT, 0, &colorArray_[0]);
        glDrawArrays(GL_TRIANGLES, 0, numTriangles_ * 3);
        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);
    }
}

}    // Namespace OpenGL.
}    // Namespace Video.
}    // Namespace Zarch.
}    // Namespace kxm.

