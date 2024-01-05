///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_SCENEGRAPH_VULKAN_COORDSYS_H_
#define VECTOID_SCENEGRAPH_VULKAN_COORDSYS_H_

#include <Vectoid/Core/FullTransform.h>
#include <Vectoid/SceneGraph/CoordSys.h>

namespace Vectoid {
namespace SceneGraph {
namespace Vulkan {

class RenderTarget;
class Context;

//! This scene graph node sets up a local coordinate system for its children.
class CoordSys : public Vectoid::SceneGraph::CoordSys {
  public:
    friend class RenderTarget;
    
    CoordSys(const CoordSys &other) = delete;
    CoordSys &operator=(const CoordSys &other) = delete;
    
    void RenderPre() override;
    void RenderPost() override;

  private:
    CoordSys(const std::shared_ptr<Context> &context);
    
    std::shared_ptr<Context> context_;
    Core::FullTransform      objectTransformBackup_;
};

}    // Namespace Vulkan.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_VULKAN_COORDSYS_H_
