#include <Vectoid/SceneGraph/OpenGL/LineSegments.h>

#include <Vectoid/Core/TwoPoints.h>
#include <Vectoid/Core/LineSegmentProviderInterface.h>
#include <Vectoid/SceneGraph/OpenGL/OpenGL.h>

using std::shared_ptr;
using Vectoid::Core::LineSegmentProviderInterface;
using Vectoid::Core::Vector;
using Vectoid::Core::TwoPoints;

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

LineSegments::LineSegments(const shared_ptr<LineSegmentProviderInterface> &lineSegmentProvider)
        : SceneGraph::LineSegments(lineSegmentProvider) {
    // Nop.
}

void LineSegments::Render() {
    glBegin(GL_LINES);
    lineSegmentProvider_->PrepareToProvideLineSegments();
    TwoPoints lineSegment;
    while (lineSegmentProvider_->ProvideNextLineSegment(&lineSegment)) {
        glVertex3f(lineSegment.point0.x, lineSegment.point0.y, lineSegment.point0.z);
        glVertex3f(lineSegment.point1.x, lineSegment.point1.y, lineSegment.point1.z);
    }
    glEnd();
}

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.
