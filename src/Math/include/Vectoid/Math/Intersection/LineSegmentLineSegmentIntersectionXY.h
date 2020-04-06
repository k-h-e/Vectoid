#ifndef VECTOID_MATH_INTERSECTION_LINESEGMENTLINESEGMENTINTERSECTIONXY_H_
#define VECTOID_MATH_INTERSECTION_LINESEGMENTLINESEGMENTINTERSECTIONXY_H_

namespace Vectoid {
namespace Core {
    template<typename T> class Vector;
    class TwoPoints;
}
}

namespace Vectoid {
namespace Math {
namespace Intersection {

//! Tests whether two line segments in the <c>x/y</c> plane intersect.
/*!
 *  \ingroup Vectoid
 */
class LineSegmentLineSegmentIntersectionXY {
  public:
    static bool Compute(const Core::TwoPoints &segment0, const Core::TwoPoints &segment1,
                        Core::Vector<float> *outIntersectionPoint);
};

}    // Namespace Intersection.
}    // Namespace Math.
}    // Namespace Vectoid.

#endif    // VECTOID_MATH_INTERSECTION_LINESEGMENTLINESEGMENTINTERSECTIONXY_H_
