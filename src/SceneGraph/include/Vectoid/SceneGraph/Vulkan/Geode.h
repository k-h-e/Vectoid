///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//                                           //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_SCENEGRAPH_VULKAN_GEODE_H_
#define VECTOID_SCENEGRAPH_VULKAN_GEODE_H_

#include <Vectoid/SceneGraph/Geode.h>

namespace Vectoid {
namespace SceneGraph {
namespace Vulkan {

class RenderTarget;

//! This scene graph node represents actual geometry in the scene (geode = geometry node).
class Geode : public Vectoid::SceneGraph::Geode {
  public:
    friend class RenderTarget;
    
    Geode(const Geode &other) = delete;
    Geode &operator=(const Geode &other) = delete;
    
  private:
    Geode(const std::shared_ptr<GeometryInterface> &geometry);
};

}    // Namespace Vulkan.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.


#endif    // VECTOID_SCENEGRAPH_VULKAN_GEODE_H_
