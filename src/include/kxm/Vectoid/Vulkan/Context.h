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
 */
class Context {
  public:
    Context();
    Context(const Context &other) = delete;
    Context &operator=(const Context &other) = delete;
    
    VkInstance instance;
    
  private:
    bool CreateInstance(const std::vector<std::string> &requiredExtensions);
};

}    // Namespace Vulkan.
}    // Namespace Vectoid.
}    // Namespace kxm.

#endif    // KXM_VECTOID_VULKAN_CONTEXT_H_
