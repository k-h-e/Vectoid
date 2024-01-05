///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/Math/Distance/PointLineSegmentDistanceXY.h>

#include <Vectoid/Core/Vector.h>
#include <Vectoid/Core/TwoPoints.h>

using Vectoid::Core::Vector;
using Vectoid::Core::TwoPoints;

namespace Vectoid {
namespace Math {
namespace Distance {

float PointLineSegmentDistanceXY::Compute(const Vector<float> &point, const TwoPoints &lineSegment) {
    Vector<float> pointXY = point;
    pointXY.z = 0.0f;
    TwoPoints segmentXY = lineSegment;
    segmentXY.point0.z = 0.0f;
    segmentXY.point1.z = 0.0f;
    Vector<float> d = segmentXY.point1 - segmentXY.point0;
    Vector<float> u = pointXY - segmentXY.point0;
    float dd = DotProduct(d, d);
    if (dd == 0.0f) {
        return u.Length();
    }
    Vector<float> nearestPoint = segmentXY.point0;
    float t = DotProduct(u, d) / dd;
    if (t >= 1.0f) {
        nearestPoint = segmentXY.point1;
    }
    else if (t > 0.0f) {
        nearestPoint = CombineAffine(t, segmentXY.point0, segmentXY.point1);
    }
    return (pointXY - nearestPoint).Length();
}


}    // Namespace Distance.
}    // Namespace Math.
}    // Namespace Vectoid.
