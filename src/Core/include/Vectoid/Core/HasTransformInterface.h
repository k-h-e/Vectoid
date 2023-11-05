///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//    All rights reserved.                   //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_CORE_HASTRANSFORMINTERFACE_H_
#define VECTOID_CORE_HASTRANSFORMINTERFACE_H_

#include <K/Core/Interface.h>

namespace Vectoid {
namespace Core {

template<typename T> class Transform;

//! Interface to entities having an associated transform, as for example a \ref CoordSys.
class HasTransformInterface : public virtual K::Core::Interface {
  public:
    //! Retrieves the associated transform.
    virtual void GetTransform(Transform<float> *outTransform) const = 0;
};

}    // Namespace Core.
}    // Namespace Vectoid.

#endif    // VECTOID_CORE_HASTRANSFORMINTERFACE_H_
