///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//    All rights reserved.                   //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/SceneGraph/Vulkan/PerspectiveProjection.h>

#include <Vectoid/SceneGraph/Vulkan/Context.h>

using namespace std;

namespace Vectoid {
namespace SceneGraph {
namespace Vulkan {

PerspectiveProjection::PerspectiveProjection(const shared_ptr<Context> &context)
    : context_(context) {
    // Nop.
}

void PerspectiveProjection::RenderPre() {
    objectTransformBackup_ = context_->ObjectTransform();
    if (parametersChanged_) {
        float windowWidth, windowHeight;
        ComputeWindowDimensions(&windowWidth, &windowHeight);
        transform_.SetFrustum(-windowWidth  / 2.0f, windowWidth  / 2.0f,
                              -windowHeight / 2.0f, windowHeight / 2.0f,
                              eyepointDistance_, eyepointDistance_ + viewingDepth_);
        transform_ = Core::FullTransform(transform_,
                                         Core::Transform<float>(Core::Vector<float>(0.0, 0.0, -eyepointDistance_)));
        parametersChanged_ = false;
    }
    context_->UpdateObjectTransform(Core::FullTransform(context_->ObjectTransform(), transform_));
}

void PerspectiveProjection::RenderPost() {
    context_->UpdateObjectTransform(objectTransformBackup_);
}

}    // Namespace Vulkan.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.
