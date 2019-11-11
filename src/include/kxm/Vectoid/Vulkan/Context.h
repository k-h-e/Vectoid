#ifndef KXM_VECTOID_VULKAN_CONTEXT_H_
#define KXM_VECTOID_VULKAN_CONTEXT_H_

#include <vector>
#include <vulkan/vulkan.h>

namespace kxm {
namespace Vectoid {
namespace Vulkan {

//! Holds <c>Vulkan</c>-specific context for scene graph nodes.
/*!
 *  \ingroup VectoidVulkan
 *
 *  Allocates Vulkan resources upon construction, and releases Vulkan resources upon destruction.
 */
class Context {
  public:
    struct FrameBufferInfo {
        VkImage        image;
        VkImageView    view;
        VkDeviceMemory memory;
        
        FrameBufferInfo() : image(VK_NULL_HANDLE), view(VK_NULL_HANDLE), memory(VK_NULL_HANDLE) {}
    };
    struct BufferInfo {
        VkBuffer       buffer;
        VkDeviceMemory memory;
        
        BufferInfo() : buffer(VK_NULL_HANDLE), memory(VK_NULL_HANDLE) {}
    };
  
    Context(void *view);
    Context(const Context &other) = delete;
    Context &operator=(const Context &other) = delete;
    ~Context();
    
    //! Tells whether the context is operative and can be used.
    /*!
     *  If it is not, it must not be used. Its destructor will properly clean things up, though.
     */
    bool Operative();
    //! Creates the command buffer.
    /*!
     *  \return <c>true</c> in case of success.
     */
    bool CreateCommandBuffer();
    //! Frees the command buffer if it is present.
    void FreeCommandBuffer();
    
    VkInstance                       instance;
    VkSurfaceKHR                     surface;
    VkDevice                         device;
    VkPhysicalDevice                 physicalDevice;                    // Valid <=> device present.
    VkPhysicalDeviceMemoryProperties physicalDeviceMemoryProperties;    // Valid <=> device present.
    uint32_t                         queueFamilyCount;                  // Valid <=> device present.
    uint32_t                         graphicsQueueFamilyIndex;          // Valid <=> device present.
    uint32_t                         presentQueueFamilyIndex;           // Valid <=> device present.
    VkSwapchainKHR                   swapChain;
    uint32_t                         width;                             // Valid <=> swap chain present.
    uint32_t                         height;                            // Valid <=> swap chain present.
    std::vector<FrameBufferInfo>     colorBuffers;
    FrameBufferInfo                  depthBuffer;
    BufferInfo                       uniformBuffer;
    VkCommandPool                    commandBufferPool;
    VkCommandBuffer                  commandBuffer;
    
  private:
    bool CreateInstance();
    // Frees the instance if it is present.
    void FreeInstance();
    bool CreateSurface(void *view);
    // Frees the surface if it is present.
    void FreeSurface();
    bool CreateDevice();
    // Frees the device if it is present.
    void FreeDevice();
    bool CreateSwapChain();
    // Frees the swap chain if it is present.
    void FreeSwapChain();
    bool CreateDepthBuffer();
    // Frees the depth buffer if it is present.
    void FreeDepthBuffer();
    bool CreateUniformBuffer();
    // Frees the uniform buffer if it is present.
    void FreeUniformBuffer();
    bool CreateCommandBufferPool();
    // Frees the command buffer pool if it is present.
    void FreeCommandBufferPool();
    
    bool getMemoryIndex(uint32_t typeBits, VkFlags requirementsMask, uint32_t *typeIndex);
    
    bool operative_;
};

}    // Namespace Vulkan.
}    // Namespace Vectoid.
}    // Namespace kxm.

#endif    // KXM_VECTOID_VULKAN_CONTEXT_H_
