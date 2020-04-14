#include <Vectoid/SceneGraph/LineSegments.h>

using std::shared_ptr;
using Vectoid::Core::LineSegmentProviderInterface;

namespace Vectoid {
namespace SceneGraph {

LineSegments::LineSegments(const shared_ptr<LineSegmentProviderInterface> &lineSegmentProvider)
        : lineSegmentProvider_(lineSegmentProvider),
          color_(.8f, .8f, .8f) {
    // Nop.
}

void LineSegments::SetColor(const Core::Vector<float> &color) {
    color_ = color;
}

}    // Namespace SceneGraph.
}    // Namespace Vectoid.
