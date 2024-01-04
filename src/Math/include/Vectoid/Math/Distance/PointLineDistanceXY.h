///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//                                           //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_MATH_DISTANCE_POINTLINEDISTANCEXY_H_
#define VECTOID_MATH_DISTANCE_POINTLINEDISTANCEXY_H_

namespace Vectoid {
namespace Core {
    template<typename T> class Vector;
    class TwoPoints;
}
}

namespace Vectoid {
namespace Math {
namespace Distance {

//! Computes the distance from a point in the <c>x/y</c> plane to a line inside the <c>x/y</c> plane.
class PointLineDistanceXY {
  public:
    static bool ComputeSigned(const Core::Vector<float> &point, const Core::TwoPoints &line, float *outDistance);
};

}    // Namespace Distance.
}    // Namespace Math.
}    // Namespace Vectoid.

#endif    // VECTOID_MATH_DISTANCE_POINTLINEDISTANCEXY_H_

