///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/SceneGraph/Vulkan/CoordSys.h>

#include <Vectoid/SceneGraph/Vulkan/Context.h>

using namespace std;

namespace Vectoid {
namespace SceneGraph {
namespace Vulkan {

CoordSys::CoordSys(const shared_ptr<Context> &context)
        : Vectoid::SceneGraph::CoordSys(),
          context_(context) {
    // Nop.
}

void CoordSys::RenderPre() {
    objectTransformBackup_ = context_->ObjectTransform();
    context_->UpdateObjectTransform(Core::FullTransform(context_->ObjectTransform(), transform_));
}

void CoordSys::RenderPost() {
    context_->UpdateObjectTransform(objectTransformBackup_);
}

}    // Namespace Vulkan.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.
