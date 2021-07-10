#include <Vectoid/SceneGraph/OpenGL/LitColorCodedTriangles.h>

#include <K/Core/NumberTools.h>
#include <Vectoid/Core/ThreePoints.h>
#include <Vectoid/Core/TriangleProviderInterface.h>
#include <Vectoid/SceneGraph/OpenGL/OpenGL.h>

using std::shared_ptr;
using K::Core::NumberTools;
using Vectoid::Core::TriangleProviderInterface;
using Vectoid::Core::Vector;
using Vectoid::Core::ThreePoints;

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

LitColorCodedTriangles::LitColorCodedTriangles(const shared_ptr<TriangleProviderInterface> &triangleProvider)
        : SceneGraph::LitColorCodedTriangles(triangleProvider) {
    // Nop.
}

void LitColorCodedTriangles::Render() {
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);

    glBegin(GL_TRIANGLES);
    triangleProvider_->PrepareToProvideTriangles();
    ThreePoints   triangle;
    Vector<float> normal, color;
    while (triangleProvider_->ProvideNextTriangle(&triangle)) {
        triangleProvider_->ProvideNormal(&normal);
        glNormal3f(normal.x, normal.y, normal.z);
        color = GetColor(triangle.point0);
        glColor3f(color.x, color.y, color.z);
        glVertex3f(triangle.point0.x, triangle.point0.y, triangle.point0.z);
        color = GetColor(triangle.point1);
        glColor3f(color.x, color.y, color.z);
        glVertex3f(triangle.point1.x, triangle.point1.y, triangle.point1.z);
        color = GetColor(triangle.point2);
        glColor3f(color.x, color.y, color.z);
        glVertex3f(triangle.point2.x, triangle.point2.y, triangle.point2.z);
    }
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);
}

Vector<float> LitColorCodedTriangles::GetColor(const Vector<float> &vertex) {
    auto color = colorCodingFunction_ ? colorCodingFunction_(vertex) : Vector<float>(.5f, .5f, .5f);
    color.ClampComponents(0.0f, 1.0f);
    return color;
}

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.
