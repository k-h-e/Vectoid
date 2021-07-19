#include <Vectoid/Math/Intersection/LineBoundingBoxIntersection.h>

#include <Vectoid/Core/BoundingBox.h>

using std::numeric_limits;
using Vectoid::Core::Vector;
using Vectoid::Core::BoundingBox;

namespace Vectoid {
namespace Math {
namespace Intersection {

bool LineBoundingBoxIntersection::Compute(const Vector<float> &linePoint, const Vector<float> &lineDirection,
                                          const BoundingBox<float> &boundingBox, bool *outIntersects) {
    Vector<float> minCorner = boundingBox.MinCorner();
    Vector<float> maxCorner = boundingBox.MaxCorner();

    float tNear = numeric_limits<float>::min();
    float tFar  = numeric_limits<float>::max();
    for (int axis = 0; axis < 3; ++axis) {
       if (lineDirection[axis] == 0.0f) {
           // The line is parallel to the min[axis] and max[axis] planes.
           if ((linePoint[axis] < minCorner[axis]) || (linePoint[axis] > maxCorner[axis])) {
               *outIntersects = false;
               return true;
           } else {
               continue;    // Continue testing the other slabs.
           }
       }
       // The line is not parallel to the slab planes, so compute the parameters of intersection.  The line segment of
       // intersection is P+t*d, where t0 <= t <= t1.
       float t0 = (minCorner[axis] - linePoint[axis]) / lineDirection[axis];
       float t1 = (maxCorner[axis] - linePoint[axis]) / lineDirection[axis];
       if (!std::isfinite(t0) || !std::isfinite(t1)) {
           return false;
       }
       if (t0 > t1) {
           NumberTools::Swap(&t0, &t1);
       }
       if (t0 > tNear) {
           tNear = t0;
       }
       if (t1 < tFar) {
           tFar = t1;
       }

       if (tNear > tFar) {
           *outIntersects = false;    // The line misses the AABB.
           return true;
       }
    }

    *outIntersects = true;
    return true;
}

}    // Namespace Intersection.
}    // Namespace Math.
}    // Namespace Vectoid.
