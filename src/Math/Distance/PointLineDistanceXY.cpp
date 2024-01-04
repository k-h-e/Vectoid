///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//                                           //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/Math/Distance/PointLineDistanceXY.h>

#include <Vectoid/Core/Vector.h>
#include <Vectoid/Core/TwoPoints.h>

using Vectoid::Core::Vector;
using Vectoid::Core::TwoPoints;

namespace Vectoid {
namespace Math {
namespace Distance {

bool PointLineDistanceXY::ComputeSigned(const Vector<float> &point, const TwoPoints &line, float *outDistance) {
    Vector<float> direction = line.point1 - line.point0;
    Vector<float> normal(direction.y, -direction.x, 0.0f);
    normal.Normalize();
    if (normal.Valid()) {
        Vector<float> pointXY(point.x, point.y, 0.0f);
        Vector<float> linePoint0XY(line.point0.x, line.point0.y, 0.0f);
        *outDistance = DotProduct(pointXY - linePoint0XY, normal);
        return true;
    }

    return false;
}


}    // Namespace Distance.
}    // Namespace Math.
}    // Namespace Vectoid.
