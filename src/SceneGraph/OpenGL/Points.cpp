#include <Vectoid/SceneGraph/OpenGL/Points.h>

#include <Vectoid/Core/TwoPoints.h>
#include <Vectoid/DataSet/VertexSet.h>
#include <Vectoid/SceneGraph/OpenGL/OpenGL.h>

using std::shared_ptr;
using Vectoid::Core::Vector;
using Vectoid::DataSet::VertexSet;

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

Points::Points(const shared_ptr<VertexSet> &points)
        : SceneGraph::Points(points) {
    // Nop.
}

void Points::Render() {
    glColor3f(color_.x, color_.y, color_.z);
    glBegin(GL_POINTS);
    for (int i = 0; i < points_->Count(); ++i) {
        auto &point = (*points_)[i];
        glVertex3f(point.x, point.y, point.z);
    }
    glEnd();
    glColor3f(1.0f, 1.0f, 1.0f);
}

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.