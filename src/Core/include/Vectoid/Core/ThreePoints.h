#ifndef VECTOID_CORE_THREEPOINTS_H_
#define VECTOID_CORE_THREEPOINTS_H_

#include <Vectoid/Core/Tools.h>
#include <Vectoid/Core/Vector.h>

namespace Vectoid {
namespace Core {

//! Three points in 3-space, with meaningful ordering.
class ThreePoints {
  public:
    struct HashFunction;

    ThreePoints() {}
    ThreePoints(const Vector<float> &aPoint0, const Vector<float> &aPoint1, const Vector<float> &aPoint2)
        : point0(aPoint0), point1(aPoint1), point2(aPoint2) {}
    // Default copy and move, ok.

    bool operator==(const ThreePoints &other) const {
        return (point0 == other.point0) && (point1 == other.point1) && (point2 == other.point2);
    }

    std::size_t Hash() const {
        std::size_t hash = 17u;
        hash = hash*31u + point0.Hash();
        hash = hash*31u + point1.Hash();
        hash = hash*31u + point2.Hash();
        return hash;
    }

    //! Gives access to the specified point. Does mod 3 on index.
    Vector<float> &operator[](int index) {
        switch (Tools::IndexMod3(index)) {
            case 1:
                return point1;
            case 2:
                return point2;
            default:
                return point0;
        }
    }

    //! Gives access to the specified point. Does mod 3 on index.
    const Vector<float> &operator[](int index) const {
        switch (Tools::IndexMod3(index)) {
            case 1:
                return point1;
            case 2:
                return point2;
            default:
                return point0;
        }
    }

    //! Computes the normal for the triangle given by the three points.
    /*!
     *  The returned normal might not be a <c>Valid()</c> vector.
     */
    void ComputeNormal(Vector<float> *outNormal) const {
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

struct ThreePoints::HashFunction {
    std::size_t operator()(const ThreePoints &threePoints) const {
        return threePoints.Hash();
    }
};

}    // Namespace Core.
}    // Namespace Vectoid.

#endif    // VECTOID_CORE_THREEPOINTS_H_
