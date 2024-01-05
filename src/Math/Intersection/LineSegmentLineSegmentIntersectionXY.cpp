///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/Math/Intersection/LineSegmentLineSegmentIntersectionXY.h>

#include <Vectoid/Core/TwoPoints.h>

using Vectoid::Core::Vector;
using Vectoid::Core::TwoPoints;
using Vectoid::Math::Intersection::LineSegmentLineSegmentIntersectionXY;

namespace Vectoid {
namespace Math {
namespace Intersection {

bool LineSegmentLineSegmentIntersectionXY::Compute(const TwoPoints &segment0, const TwoPoints &segment1,
                                                   Vector<float> *outIntersectionPoint) {
    TwoPoints segmentXY0 = segment0;
    TwoPoints segmentXY1 = segment1;
    segmentXY0.point0.z = 0.0f;
    segmentXY0.point1.z = 0.0f;
    segmentXY1.point0.z = 0.0f;
    segmentXY1.point1.z = 0.0f;
    Vector<float> dir = segmentXY0.point1 - segmentXY0.point0;
    Vector<float> n(-dir.y, dir.x, 0.0f);
    float  d0 = DotProduct((segmentXY1.point0 - segmentXY0.point0), n);
    float  d1 = DotProduct((segmentXY1.point1 - segmentXY0.point0), n);
    if (!(   ((d0 >  0.0f) && (d1 <= 0.0f))
          || ((d0 <= 0.0f) && (d1 >  0.0f)))) {
        return false;
    }
    dir = segmentXY1.point1 - segmentXY1.point0;
    n   = Vector<float>(-dir.y, dir.x, 0.0f);
    d0  = DotProduct((segmentXY0.point0 - segmentXY1.point0), n);
    d1  = DotProduct((segmentXY0.point1 - segmentXY1.point0), n);
    if (!(   ((d0 >  0.0f) && (d1 <= 0.0f))
          || ((d0 <= 0.0f) && (d1 >  0.0f)))) {
        return false;
    }

    if (d0 < 0.0f) {
        d0 = -d0;
    }
    if (d1 < 0.0f) {
        d1 = -d1;
    }
    *outIntersectionPoint = CombineConvex(d0, d1, segmentXY0.point0, segmentXY0.point1);
    return true;
}

}    // Namespace Intersection.
}    // Namespace Math.
}    // Namespace Vectoid.
