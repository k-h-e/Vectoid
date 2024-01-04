///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//                                           //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/SceneGraph/Vulkan/LineSegments.h>

#include <Vectoid/Core/LineSegmentProviderInterface.h>

using std::shared_ptr;
using Vectoid::Core::LineSegmentProviderInterface;

namespace Vectoid {
namespace SceneGraph {
namespace Vulkan {

LineSegments::LineSegments(const shared_ptr<LineSegmentProviderInterface> &lineSegmentProvider)
        : SceneGraph::LineSegments(lineSegmentProvider) {
    // Nop.
}

void LineSegments::Render() {
    // Not yet implemented.
}

}    // Namespace Vulkan.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.
