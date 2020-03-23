#include <kxm/Vectoid/OpenGL/LitTriangles.h>

#include <kxm/Vectoid/ThreePoints.h>
#include <kxm/Vectoid/TriangleProviderInterface.h>
#include <kxm/Vectoid/OpenGL/OpenGL.h>

using std::shared_ptr;

namespace kxm {
namespace Vectoid {
namespace OpenGL {

LitTriangles::LitTriangles(const shared_ptr<TriangleProviderInterface> &triangleProvider)
        : Vectoid::LitTriangles(triangleProvider) {
    // Nop.
}

void LitTriangles::Render() {
    glEnable(GL_LIGHTING);

    glBegin(GL_TRIANGLES);
    triangleProvider_->PrepareToProvideTriangles();
    ThreePoints triangle;
    Vector      normal;
    while (triangleProvider_->ProvideNextTriangle(&triangle)) {
        triangleProvider_->ProvideNormal(&normal);
        glNormal3f(normal.x, normal.y, normal.z);
        glVertex3f(triangle.point0.x, triangle.point0.y, triangle.point0.z);
        glVertex3f(triangle.point1.x, triangle.point1.y, triangle.point1.z);
        glVertex3f(triangle.point2.x, triangle.point2.y, triangle.point2.z);
    }
    glEnd();

    glDisable(GL_LIGHTING);
}

}    // Namespace OpenGL.
}    // Namespace Vectoid.
}    // Namespace kxm.
