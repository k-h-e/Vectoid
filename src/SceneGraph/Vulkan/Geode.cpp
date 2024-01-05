///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/SceneGraph/Vulkan/Geode.h>

#include <K/Core/Log.h>

using namespace std;
using K::Core::Log;

namespace Vectoid {
namespace SceneGraph {
namespace Vulkan {

Geode::Geode(const shared_ptr<GeometryInterface> &geometry)
        : Vectoid::SceneGraph::Geode(geometry) {
    // Nop.
}

}    // Namespace Vulkan.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.
