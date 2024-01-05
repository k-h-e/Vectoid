///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/SceneGraph/Geode.h>

#include <Vectoid/SceneGraph/Geometry.h>

using std::shared_ptr;

namespace Vectoid {
namespace SceneGraph {

Geode::Geode(const shared_ptr<Context> &context, const shared_ptr<Geometry> &geometry)
        : TreeNode(context),
          geometry_(geometry) {
    // Nop.
}

void Geode::SetGeometry(const std::shared_ptr<Geometry> &geometry) {
    geometry_ = geometry;
}

void Geode::RenderPre() {
    if (geometry_) {
        geometry_->Render();
    }
}

}    // Namespace SceneGraph.
}    // Namespace Vectoid.
