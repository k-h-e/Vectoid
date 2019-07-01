#ifndef KXM_VECTOID_VULKAN_CONTEXT_H_
#define KXM_VECTOID_VULKAN_CONTEXT_H_

#include <string>
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
    Context(void *view);
    Context(const Context &other) = delete;
    Context &operator=(const Context &other) = delete;
    ~Context();
    
    //! Tells whether the context is operative and can be used.
    /*!
     *  If it is not, it must not be used. Its destructor will properly clean things up, though.
     */
    bool Operative();
    
    VkInstance      instance;
    VkSurfaceKHR    surface;
    VkDevice        device;
    uint32_t        queueFamilyIndex;     // Valid <=> device present.
    VkCommandPool   commandBufferPool;
    VkCommandBuffer commandBuffer;
    
  private:
    bool CreateInstance(const std::vector<std::string> &requiredExtensions);
    bool CreateSurface(void *view);
    bool CreateDevice(const std::vector<std::string> &requiredExtensions);
    bool CreateCommandBufferPool();
    
    bool operative_;
};

}    // Namespace Vulkan.
}    // Namespace Vectoid.
}    // Namespace kxm.

#endif    // KXM_VECTOID_VULKAN_CONTEXT_H_
