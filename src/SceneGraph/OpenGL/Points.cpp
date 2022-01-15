#include <Vectoid/SceneGraph/OpenGL/Points.h>

#include <Vectoid/Core/TwoPoints.h>
#include <Vectoid/DataSet/Points.h>
#include <Vectoid/SceneGraph/OpenGL/Context.h>
#include <Vectoid/SceneGraph/OpenGL/OpenGL.h>

using std::shared_ptr;
using Vectoid::Core::Vector;

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

Points::Points(const shared_ptr<Context> &context, const shared_ptr<DataSet::Points> &points)
        : SceneGraph::Points(context, points) {
    // Nop.
}

void Points::Render() {
    glColor3f(color_.x, color_.y, color_.z);
    glBegin(GL_POINTS);
    for (int i = 0; i < points_->Size(); ++i) {
        auto &point = (*points_)[i];
        glVertex3f(point.x, point.y, point.z);
    }
    glEnd();
    glColor3f(1.0f, 1.0f, 1.0f);
}

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.
