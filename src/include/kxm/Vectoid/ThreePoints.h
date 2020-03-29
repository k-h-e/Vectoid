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
    ThreePoints(const Vector<float> &aPoint0, const Vector<float> &aPoint1, const Vector<float> &aPoint2)
        : point0(aPoint0), point1(aPoint1), point2(aPoint2) {}
    // Default copy and move, ok.

    //! Computes the normal for the triangle given by the three points.
    /*!
     *  The returned normal might not be a <c>Valid()</c> vector.
     */
    void ComputeNormal(Vector<float> *outNormal) {
        *outNormal = CrossProduct(point1 - point0, point2 - point0);
        outNormal->Normalize();
    }

    Vector<float> point0;
    Vector<float> point1;
    Vector<float> point2;
};

}    // Namespace Vectoid.
}    // Namespace kxm.

#endif    // KXM_VECTOID_THREEPOINTS_H_
