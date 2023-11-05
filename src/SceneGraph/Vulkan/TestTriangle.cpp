///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//    All rights reserved.                   //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/SceneGraph/Vulkan/TestTriangle.h>

#include <K/Core/Log.h>

using namespace std;
using K::Core::Log;

namespace Vectoid {
namespace SceneGraph {
namespace Vulkan {

TestTriangle::TestTriangle(const shared_ptr<Context> &context)
        : Vectoid::SceneGraph::TestTriangle(),
          context_(context) {
    // Nop.
}

void TestTriangle::Render() {
    Log::Print(Log::Level::Debug, this, []{ return "Vulkan::TestTriangle::Render()"; });
}

}    // Namespace Vulkan.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.
