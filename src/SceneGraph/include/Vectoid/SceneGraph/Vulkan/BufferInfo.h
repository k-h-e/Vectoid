///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//    All rights reserved.                   //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_SCENEGRAPH_VULKAN_BUFFERINFO_H_
#define VECTOID_SCENEGRAPH_VULKAN_BUFFERINFO_H_

#include <vulkan/vulkan.h>

namespace Vectoid {
namespace SceneGraph {
namespace Vulkan {

//! Holds info about a <c>Vulkan</c> buffer.
struct BufferInfo {
    VkBuffer               buffer;
    VkDeviceMemory         memory;
    VkDescriptorBufferInfo info;
    
    BufferInfo() : buffer(VK_NULL_HANDLE), memory(VK_NULL_HANDLE) {
        info.buffer = VK_NULL_HANDLE;
        info.offset = 0u;
        info.range  = 0u;
    }
    // Default copy okay.
};

}    // Namespace Vulkan.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_VULKAN_BUFFERINFO_H_
