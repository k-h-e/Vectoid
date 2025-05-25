///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_CORE_TRIANGLEHANDLERINTERFACE_H_
#define VECTOID_CORE_TRIANGLEHANDLERINTERFACE_H_

#include <K/Core/StreamHandlerInterface.h>

namespace Vectoid {
    namespace Core {
        class ThreePoints;
    }
}

namespace Vectoid {
namespace Core {

//! Interface to entities handling a stream of triangles.
class TriangleHandlerInterface : public virtual K::Core::StreamHandlerInterface {
  public:
    //! Hands over the next triangle to the handler.
    virtual void OnTriangle(const ThreePoints &triangle) = 0;
};

}    // Namespace Core.
}    // Namespace Vectoid.

#endif    // VECTOID_CORE_TRIANGLEHANDLERINTERFACE_H_
