///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//                                           //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_SCENEGRAPH_VULKAN_FRAMEBUFFERINFO_H_
#define VECTOID_SCENEGRAPH_VULKAN_FRAMEBUFFERINFO_H_

#include <vulkan/vulkan.h>

namespace Vectoid {
namespace SceneGraph {
namespace Vulkan {

//! Holds info about a <c>Vulkan</c> frame buffer.
struct FrameBufferInfo {
    VkImage        image;
    VkImageView    view;
    VkDeviceMemory memory;
  
    FrameBufferInfo() : image(VK_NULL_HANDLE), view(VK_NULL_HANDLE), memory(VK_NULL_HANDLE) {}
    // Default copy okay.
};

}    // Namespace Vulkan.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_VULKAN_FRAMEBUFFERINFO_H_
