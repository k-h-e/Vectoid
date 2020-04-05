#ifndef VECTOID_CORE_THREEPOINTS_H_
#define VECTOID_CORE_THREEPOINTS_H_

#include <Vectoid/Core/Vector.h>

namespace Vectoid {
namespace Core {

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

    //! Tells whether the specified point is one of the three points.
    bool Contains(const Vector<float> &point) {
        return (point0 == point) || (point1 == point) || (point2 == point);
    }

    Vector<float> point0;
    Vector<float> point1;
    Vector<float> point2;
};

}    // Namespace Core.
}    // Namespace Vectoid.

#endif    // VECTOID_CORE_THREEPOINTS_H_
