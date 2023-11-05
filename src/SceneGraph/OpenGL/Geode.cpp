///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//    All rights reserved.                   //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/SceneGraph/OpenGL/Geode.h>

#include <Vectoid/SceneGraph/OpenGL/Context.h>

using std::shared_ptr;

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

Geode::Geode(const shared_ptr<Context> &context, const shared_ptr<Geometry> &geometry)
        : SceneGraph::Geode(context, geometry) {
    // Nop.
}

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.
