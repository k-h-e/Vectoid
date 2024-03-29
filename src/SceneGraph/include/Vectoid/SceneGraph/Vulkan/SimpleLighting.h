///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_SCENEGRAPH_VULKAN_SIMPLELIGHTING_H_
#define VECTOID_SCENEGRAPH_VULKAN_SIMPLELIGHTING_H_

#include <Vectoid/SceneGraph/SimpleLighting.h>

namespace Vectoid {
namespace SceneGraph {
namespace Vulkan {

//! Simple lighting setup using one light source.
class SimpleLighting : public Vectoid::SceneGraph::SimpleLighting {
  public:
    SimpleLighting();
    SimpleLighting(const SimpleLighting &other)             = delete;
    SimpleLighting &operator=(const SimpleLighting &other)  = delete;
    SimpleLighting(const SimpleLighting &&other)            = delete;
    SimpleLighting &operator=(const SimpleLighting &&other) = delete;
    virtual void Render();
};

}    // Namespace Vulkan.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_VULKAN_SIMPLELIGHTING_H_
