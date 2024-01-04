///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//                                           //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/SceneGraph/CoordSys.h>

using std::shared_ptr;

namespace Vectoid {
namespace SceneGraph {

CoordSys::CoordSys(const shared_ptr<Context> &context)
        : CoordSysCore(context) {
    // Nop.
}

}    // Namespace SceneGraph.
}    // Namespace Vectoid.
