///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//    All rights reserved.                   //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/Core/PointCollisionChecker.h>

#include <cstdio>
#include <Vectoid/Core/BoundingBoxCollisionChecker.h>

namespace Vectoid {
namespace Core {

bool PointCollisionChecker::CheckCollision(CollisionCheckerInterface *other, const Transform<float> &otherTransform,
                                           const Transform<float> &ourTransform) {
    return other->CheckCollision(this, ourTransform, otherTransform);
}

bool PointCollisionChecker::CheckCollision(BoundingBoxCollisionChecker *other, const Transform<float> &otherTransform,
                                           const Transform<float> &ourTransform) {
    return other->CheckCollision(this, ourTransform, otherTransform);
}

bool PointCollisionChecker::CheckCollision(PointCollisionChecker *other, const Transform<float> &otherTransform,
                                           const Transform<float> &ourTransform) {
    (void)other;
    (void)otherTransform;
    (void)ourTransform;
    return false;    // TODO: Implement check!
}

}    // Namespace Core.
}    // Namespace Vectoid.
