///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//    All rights reserved.                   //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/SceneGraph/Camera.h>

using std::shared_ptr;

namespace Vectoid {
namespace SceneGraph {

Camera::Camera(const shared_ptr<Context> &context)
        : CoordSysCore(context) {
    // Nop.
}

}    // Namespace SceneGraph.
}    // Namespace Vectoid.
