///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_CORE_THREEPOINTS_H_
#define VECTOID_CORE_THREEPOINTS_H_

#include <string>

#include <Vectoid/Core/Tools.h>
#include <Vectoid/Core/TwoPoints.h>
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

    bool Valid() const {
        return point0.Valid() && point1.Valid() && point2.Valid();
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

    //! For indices <c>0, 1, 2</c> the method returns the triangle edges <c>(point0, point1), (point1, point2)</c> and
    //! <c>(point2, point0)</c> respectively. Does mod 3 on index.
    TwoPoints TriangleEdge(int index) const {
        switch (Tools::IndexMod3(index)) {
            case 0:
                return TwoPoints{point0, point1};
                break;
            case 1:
                return TwoPoints{point1, point2};
                break;
            default:
                return TwoPoints{point2, point0};
                break;
        }
    } 

    //! Computes the normal for the triangle given by the three points.
    /*!
     *  The returned normal might not be a <c>Valid()</c> vector.
     */
    Vector<float> Normal() const {
        Vector<float> normal { CrossProduct(point1 - point0, point2 - point0) };
        normal.Normalize();
        return normal;
    }

    //! Tells whether the specified point is one of the three points.
    bool Contains(const Vector<float> &point) {
        return (point0 == point) || (point1 == point) || (point2 == point);
    }

    //! Tells the center of gravity of the three points.
    Vector<float> CenterOfGravity() const {
        return (1.0f/3.0f)*point0 + (1.0f/3.0f)*point1 + (1.0f/3.0f)*point2;
    }

    //! Produces a verbose representation of the current object state.
    std::string ToString() const {
        return std::string("(") + point0.ToString() + ", " + point1.ToString() + ", " + point2.ToString() + ")"; 
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
