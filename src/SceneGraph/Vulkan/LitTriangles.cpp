///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//                                           //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/SceneGraph/Vulkan/LitTriangles.h>

#include <Vectoid/Core/TriangleProviderInterface.h>

using std::shared_ptr;
using Vectoid::Core::TriangleProviderInterface;

namespace Vectoid {
namespace SceneGraph {
namespace Vulkan {

LitTriangles::LitTriangles(const shared_ptr<TriangleProviderInterface> &triangleProvider)
        : SceneGraph::LitTriangles(triangleProvider) {
    // Nop.
}

void LitTriangles::Render() {
    // Not yet implemented.
}

}    // Namespace Vulkan.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.
