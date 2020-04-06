#include <Vectoid/SceneGraph/OpenGL/LitTriangles.h>

#include <Vectoid/Core/ThreePoints.h>
#include <Vectoid/Core/TriangleProviderInterface.h>
#include <Vectoid/SceneGraph/OpenGL/OpenGL.h>

using std::shared_ptr;
using Vectoid::Core::TriangleProviderInterface;
using Vectoid::Core::Vector;
using Vectoid::Core::ThreePoints;

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

LitTriangles::LitTriangles(const shared_ptr<TriangleProviderInterface> &triangleProvider)
        : SceneGraph::LitTriangles(triangleProvider) {
    // Nop.
}

void LitTriangles::Render() {
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glColor3f(color_.x, color_.y, color_.z);

    glBegin(GL_TRIANGLES);
    triangleProvider_->PrepareToProvideTriangles();
    ThreePoints   triangle;
    Vector<float> normal;
    while (triangleProvider_->ProvideNextTriangle(&triangle)) {
        triangleProvider_->ProvideNormal(&normal);
        glNormal3f(normal.x, normal.y, normal.z);
        glVertex3f(triangle.point0.x, triangle.point0.y, triangle.point0.z);
        glVertex3f(triangle.point1.x, triangle.point1.y, triangle.point1.z);
        glVertex3f(triangle.point2.x, triangle.point2.y, triangle.point2.z);
    }
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);
}

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.
