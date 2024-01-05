///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_CORE_COLLISIONCHECKERINTERFACE_H_
#define VECTOID_CORE_COLLISIONCHECKERINTERFACE_H_

#include <K/Core/Interface.h>

namespace Vectoid {
namespace Core {

template<typename T> class Transform;
class BoundingBoxCollisionChecker;
class PointCollisionChecker;

//! Interface to objects performing collision checks between pairs of objects using a double-dispatch scheme.
class CollisionCheckerInterface : public virtual K::Core::Interface {
  public:
    //! Checks for collision with the specified other collision checker.
    /*!
     *  \return <c>true</c> in case a collision was detected.
     */
    virtual bool CheckCollision(CollisionCheckerInterface *other, const Transform<float> &otherTransform,
                                const Transform<float> &ourTransform) = 0;
    //! Checks for collision with the specified bounding box.
    /*!
     *  \return <c>true</c> in case a collision was detected.
     */
    virtual bool CheckCollision(BoundingBoxCollisionChecker *other, const Transform<float> &otherTransform,
                                const Transform<float> &ourTransform) = 0;
    //! Checks for collision with the specified point.
    /*!
     *  \return <c>true</c> in case a collision was detected.
     */
    virtual bool CheckCollision(PointCollisionChecker *other, const Transform<float> &otherTransform,
                                const Transform<float> &ourTransform) = 0;
};

}    // Namespace Core.
}    // Namespace Vectoid.

#endif    // VECTOID_CORE_COLLISIONCHECKERINTERFACE_H_
