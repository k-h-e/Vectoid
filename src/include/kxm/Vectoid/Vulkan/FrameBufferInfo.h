#ifndef KXM_VECTOID_VULKAN_FRAMEBUFFERINFO_H_
#define KXM_VECTOID_VULKAN_FRAMEBUFFERINFO_H_

#include <vulkan/vulkan.h>

namespace kxm {
namespace Vectoid {
namespace Vulkan {

//! Holds info about a <c>Vulkan</c> frame buffer.
/*!
 *  \ingroup VectoidVulkan
 */
struct FrameBufferInfo {
    VkImage        image;
    VkImageView    view;
    VkDeviceMemory memory;
  
    FrameBufferInfo() : image(VK_NULL_HANDLE), view(VK_NULL_HANDLE), memory(VK_NULL_HANDLE) {}
    // Default copy okay.
};

}    // Namespace Vulkan.
}    // Namespace Vectoid.
}    // Namespace kxm.

#endif    // KXM_VECTOID_VULKAN_FRAMEBUFFERINFO_H_
