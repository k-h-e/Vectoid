#ifndef KXM_VECTOID_VULKAN_BUFFERINFO_H_
#define KXM_VECTOID_VULKAN_BUFFERINFO_H_

#include <vulkan/vulkan.h>

namespace kxm {
namespace Vectoid {
namespace Vulkan {

//! Holds info about a <c>Vulkan</c> buffer.
/*!
 *  \ingroup VectoidVulkan
 */
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
}    // Namespace Vectoid.
}    // Namespace kxm.

#endif    // KXM_VECTOID_VULKAN_BUFFERINFO_H_
