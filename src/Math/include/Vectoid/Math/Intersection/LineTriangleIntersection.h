///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//    All rights reserved.                   //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_MATH_INTERSECTION_LINETRIANGLEINTERSECTION_H_
#define VECTOID_MATH_INTERSECTION_LINETRIANGLEINTERSECTION_H_

namespace Vectoid {
namespace Core {
    class ThreePoints;
    template<typename T> class Vector;
}
}

namespace Vectoid {
namespace Math {
namespace Intersection {

//! Computes the intersection between a line and a triangle.
class LineTriangleIntersection {
  public:
    //! Computes the intersection between a line and a triangle.
    /*!
     *  \param lineDirection
     *  Must be of Unit-length.
     *
     *  \param outIntersectionPoint
     *  Will only be valid in case the computation was successful and an intersection has been found.
     *
     *  \return <c>false</c> in case the computation failed. The output parameters will then be undefined.
     */
    static bool Compute(
        const Core::Vector<float> &linePoint, const Core::Vector<float> &lineDirection,
        const Core::ThreePoints &triangle, bool *outIntersects, Core::Vector<float> *outIntersectionPoint);
};

}    // Namespace Intersection.
}    // Namespace Math.
}    // Namespace Vectoid.

#endif    // VECTOID_MATH_INTERSECTION_LINETRIANGLEINTERSECTION_H_
