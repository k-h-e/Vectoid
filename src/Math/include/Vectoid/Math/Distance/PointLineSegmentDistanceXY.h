///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_MATH_DISTANCE_POINTLINESEGMENTDISTANCEXY_H_
#define VECTOID_MATH_DISTANCE_POINTLINESEGMENTDISTANCEXY_H_

namespace Vectoid {
namespace Core {
    template<typename T> class Vector;
    class TwoPoints;
}
}

namespace Vectoid {
//! Fundamental mathematics for 3D data processing.
namespace Math {
//! Algorithms to compute distances between various kinds of entities in 3-space.
namespace Distance {

//! Computes the distance from a point in the <c>x/y</c> plane to a line segment inside the <c>x/y</c> plane.
class PointLineSegmentDistanceXY {
  public:
    static float Compute(const Core::Vector<float> &point, const Core::TwoPoints &lineSegment);
};

}    // Namespace Distance.
}    // Namespace Math.
}    // Namespace Vectoid.

#endif    // VECTOID_MATH_DISTANCE_POINTLINESEGMENTDISTANCEXY_H_

