///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_CORE_POINTHANDLERINTERFACE_H_
#define VECTOID_CORE_POINTHANDLERINTERFACE_H_

#include <K/Core/StreamHandlerInterface.h>

namespace Vectoid {
    namespace Core {
        template<typename T> class Vector;
    }
}

namespace Vectoid {
namespace Core {

//! Interface to entities handling a stream of points.
class PointHandlerInterface : public virtual K::Core::StreamHandlerInterface {
  public:
    //! Hands over the next point to the handler.
    virtual void OnPoint(const Vector<float> &point) = 0;
};

}    // Namespace Core.
}    // Namespace Vectoid.

#endif    // VECTOID_CORE_POINTHANDLERINTERFACE_H_
