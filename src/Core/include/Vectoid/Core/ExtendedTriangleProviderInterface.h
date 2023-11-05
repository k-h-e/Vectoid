///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//    All rights reserved.                   //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_CORE_EXTENDEDTRIANGLEPROVIDERINTERFACE_H_
#define VECTOID_CORE_EXTENDEDTRIANGLEPROVIDERINTERFACE_H_

#include <Vectoid/Core/TriangleProviderInterface.h>

namespace Vectoid {
namespace Core {

//! Interface to entities iteratively providing triangles, including respective vertex normals.
class ExtendedTriangleProviderInterface : public virtual TriangleProviderInterface {
  public:
    //! Provides the vertex normals for the current triangle.
    virtual void ProvideVertexNormals(ThreePoints *outVertexNormals) = 0;
};

}    // Namespace Core.
}    // Namespace Vectoid.

#endif    // VECTOID_CORE_EXTENDEDTRIANGLEPROVIDERINTERFACE_H_
