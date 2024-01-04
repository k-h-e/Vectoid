///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//                                           //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_MATH_INTERSECTION_POINTTRIANGLEINTERSECTIONXY_H_
#define VECTOID_MATH_INTERSECTION_POINTTRIANGLEINTERSECTIONXY_H_

namespace Vectoid {
namespace Core {
    template<typename T> class Vector;
    class ThreePoints;
}
}

namespace Vectoid {
namespace Math {
namespace Intersection {

//! Tests whether a point in the <c>x/y</c> plane lies inside a tringle in the <c>x/y</c>.
class PointTriangleIntersectionXY {
  public:
    static bool Compute(const Core::Vector<float> &point, const Core::ThreePoints &triangle, bool *outIntersects);
};

}    // Namespace Intersection.
}    // Namespace Math.
}    // Namespace Vectoid.

#endif    // VECTOID_MATH_INTERSECTION_POINTTRIANGLEINTERSECTIONXY_H_
