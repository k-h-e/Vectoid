///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//    All rights reserved.                   //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/Math/Intersection/PointTriangleIntersectionXY.h>

#include <Vectoid/Core/TwoPoints.h>
#include <Vectoid/Core/ThreePoints.h>
#include <Vectoid/Math/Distance/PointLineDistanceXY.h>

using Vectoid::Core::Vector;
using Vectoid::Core::TwoPoints;
using Vectoid::Core::ThreePoints;
using Vectoid::Math::Distance::PointLineDistanceXY;

namespace Vectoid {
namespace Math {
namespace Intersection {

bool PointTriangleIntersectionXY::Compute(const Vector<float> &point, const ThreePoints &triangle,
                                          bool *outIntersects) {
    float distance0;
    if (PointLineDistanceXY::ComputeSigned(point, TwoPoints(triangle.point0, triangle.point1), &distance0)) {
        float distance1;
        if (PointLineDistanceXY::ComputeSigned(point, TwoPoints(triangle.point1, triangle.point2), &distance1)) {
            float distance2;
            if (PointLineDistanceXY::ComputeSigned(point, TwoPoints(triangle.point2, triangle.point0), &distance2)) {
                *outIntersects = (distance0 <= 0.0f) && (distance1 <= 0.0f) && (distance2 <= 0.0f);
                return true;
            }
        }
    }

    return false;
}


}    // Namespace Intersection.
}    // Namespace Math.
}    // Namespace Vectoid.
