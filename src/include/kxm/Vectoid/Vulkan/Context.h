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
    struct BufferInfo {
        VkImage image;
        VkImageView view;
        
        BufferInfo() : image(VK_NULL_HANDLE), view(VK_NULL_HANDLE) {}
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
    
    VkInstance                    instance;
    VkSurfaceKHR                  surface;
    VkDevice                      device;
    std::vector<VkPhysicalDevice> physicalDevices;             // Valid <=> device present.
    uint32_t                      queueFamilyCount;            // Valid <=> device present.
    uint32_t                      graphicsQueueFamilyIndex;    // Valid <=> device present.
    uint32_t                      presentQueueFamilyIndex;     // Valid <=> device present.
    VkSwapchainKHR                swapChain;
    std::vector<BufferInfo>       buffers;
    VkCommandPool                 commandBufferPool;
    VkCommandBuffer               commandBuffer;
    
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
    bool CreateCommandBufferPool();
    // Frees the command buffer pool if it is present.
    void FreeCommandBufferPool();
    
    bool operative_;
};

}    // Namespace Vulkan.
}    // Namespace Vectoid.
}    // Namespace kxm.

#endif    // KXM_VECTOID_VULKAN_CONTEXT_H_
