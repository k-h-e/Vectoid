///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_CORE_BOUNDINGBOXCOLLISIONCHECKER_H_
#define VECTOID_CORE_BOUNDINGBOXCOLLISIONCHECKER_H_

#include <Vectoid/Core/CollisionCheckerInterface.h>

namespace Vectoid {
namespace Core {

template<typename T> class BoundingBox;
template<typename T> class Transform;

//! Adapts a bounding box for taking part in collision checking.
class BoundingBoxCollisionChecker : public virtual CollisionCheckerInterface {
  public:
    //! The specified bounding box object is expected to outlive the constructed checker instance.
    BoundingBoxCollisionChecker(const BoundingBox<float> &boundingBox);
    bool CheckCollision(CollisionCheckerInterface *other, const Transform<float> &otherTransform,
                        const Transform<float> &ourTransform);
    bool CheckCollision(BoundingBoxCollisionChecker *other, const Transform<float> &otherTransform,
                        const Transform<float> &ourTransform);
    bool CheckCollision(PointCollisionChecker *other, const Transform<float> &otherTransform,
                        const Transform<float> &ourTransform);
    
  private:
    const BoundingBox<float> &boundingBox_;
};

}    // Namespace Core.
}    // Namespace Vectoid.

#endif    // VECTOID_CORE_BOUNDINGBOXCOLLISIONCHECKER_H_
