///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/SceneGraph/Geometry.h>

using std::shared_ptr;

namespace Vectoid {
namespace SceneGraph {

Geometry::Geometry(const shared_ptr<Context> &context)
        : Node(context) {
    // Nop.
}

}    // Namespace SceneGraph.
}    // Namespace Vectoid.
