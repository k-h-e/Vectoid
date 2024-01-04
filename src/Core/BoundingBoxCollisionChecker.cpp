///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//                                           //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/Core/BoundingBoxCollisionChecker.h>

#include <cstdio>
#include <Vectoid/Core/Transform.h>
#include <Vectoid/Core/BoundingBox.h>

namespace Vectoid {
namespace Core {

BoundingBoxCollisionChecker::BoundingBoxCollisionChecker(const BoundingBox<float> &boundingBox)
        : boundingBox_(boundingBox) {
}

bool BoundingBoxCollisionChecker::CheckCollision(
        CollisionCheckerInterface *other, const Transform<float> &otherTransform,
        const Transform<float> &ourTransform) {
    return other->CheckCollision(this, ourTransform, otherTransform);
}

bool BoundingBoxCollisionChecker::CheckCollision(
        BoundingBoxCollisionChecker *other, const Transform<float> &otherTransform,
        const Transform<float> &ourTransform) {
    (void)other;
    (void)otherTransform;
    (void)ourTransform;
    return false;    // TODO: Implement check!
}

bool BoundingBoxCollisionChecker::CheckCollision(
        PointCollisionChecker *other, const Transform<float> &otherTransform, const Transform<float> &ourTransform) {
    (void)other;

    Vector<float> point;
    otherTransform.GetTranslationPart(&point);
    Transform<float> inverseOurTransform(Transform<float>::InitAsInverse, ourTransform);
    inverseOurTransform.ApplyTo(&point);
    return boundingBox_.Contains(point);
}

}    // Namespace Core.
}    // Namespace Vectoid.
