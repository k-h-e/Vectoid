///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//    All rights reserved.                   //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/SceneGraph/Vulkan/Camera.h>

#include <Vectoid/SceneGraph/Vulkan/Context.h>

using namespace std;
using Vectoid::Core::Transform;
using Vectoid::Core::FullTransform;

namespace Vectoid {
namespace SceneGraph {
namespace Vulkan {

Camera::Camera(const shared_ptr<Context> &context)
        : Vectoid::SceneGraph::Camera(),
          context_(context) {
    // Nop.
}

void Camera::RenderPre() {
    objectTransformBackup_ = context_->ObjectTransform();
    Transform<float> inverse(Transform<float>::InitAsInverse, transform_);
    context_->UpdateObjectTransform(FullTransform(context_->ObjectTransform(), inverse));
}

void Camera::RenderPost() {
    context_->UpdateObjectTransform(objectTransformBackup_);
}

}    // Namespace Vulkan.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.
