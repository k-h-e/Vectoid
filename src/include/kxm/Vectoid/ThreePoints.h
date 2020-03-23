#ifndef KXM_VECTOID_THREEPOINTS_H_
#define KXM_VECTOID_THREEPOINTS_H_

#include <kxm/Vectoid/Vector.h>

namespace kxm {
namespace Vectoid {

//! Three points in 3-space, with meaningful ordering.
/*!
 *  \ingroup Vectoid
 */
class ThreePoints {
  public:
    ThreePoints() {}
    ThreePoints(const Vector &aPoint0, const Vector &aPoint1, const Vector &aPoint2)
        : point0(aPoint0), point1(aPoint1), point2(aPoint2) {}
    // Default copy and move, ok.

    //! Computes the normal for the triangle given by the three points.
    /*!
     *  The returned normal might not be a <c>Valid()</c> vector.
     */
    void ComputeNormal(Vector *outNormal) {
        *outNormal = CrossProduct(point1 - point0, point2 - point0);
        outNormal->Normalize();
    }

    Vector point0;
    Vector point1;
    Vector point2;
};

}    // Namespace Vectoid.
}    // Namespace kxm.

#endif    // KXM_VECTOID_THREEPOINTS_H_
