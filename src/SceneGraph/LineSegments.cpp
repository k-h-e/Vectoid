#include <Vectoid/SceneGraph/LineSegments.h>

using std::shared_ptr;
using Vectoid::Core::LineSegmentProviderInterface;

namespace Vectoid {
namespace SceneGraph {

LineSegments::LineSegments(const shared_ptr<LineSegmentProviderInterface> &lineSegmentProvider)
        : lineSegmentProvider_(lineSegmentProvider) {
    // Nop.
}

}    // Namespace SceneGraph.
}    // Namespace Vectoid.
