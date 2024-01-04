///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//                                           //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_CORE_HASBOUNDINGBOXINTERFACE_H_
#define VECTOID_CORE_HASBOUNDINGBOXINTERFACE_H_

#include <K/Core/Interface.h>

namespace Vectoid {
namespace Core {

template<typename T> class BoundingBox;

//! Interface to entities having an associated bounding box.
class HasBoundingBoxInterface : public virtual K::Core::Interface {
  public:
    //! Retrieves the associated bounding box.
    virtual void GetBoundingBox(BoundingBox<float> *outBoundingBox) = 0;
};

}    // Namespace Core.
}    // Namespace Vectoid.

#endif    // VECTOID_CORE_HASBOUNDINGBOXINTERFACE_H_
