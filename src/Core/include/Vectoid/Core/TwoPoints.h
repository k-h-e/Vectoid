#ifndef VECTOID_CORE_TWOPOINTS_H_
#define VECTOID_CORE_TWOPOINTS_H_

#include <Vectoid/Core/Vector.h>

namespace Vectoid {
namespace Core {

//! Two points in 3-space, with meaningful ordering.
/*!
 *  \ingroup Vectoid
 */
class TwoPoints {
  public:
    TwoPoints() {}
    TwoPoints(const Vector<float> &aPoint0, const Vector<float> &aPoint1)
        : point0(aPoint0), point1(aPoint1) {}
    // Default copy and move, ok.

    std::string ToString() const {
        return "( " + point0.ToString() + ", " + point1.ToString() + " )";
    }

    Vector<float> point0;
    Vector<float> point1;
};

}    // Namespace Core.
}    // Namespace Vectoid.

#endif    // VECTOID_CORE_TWOPOINTS_H_
