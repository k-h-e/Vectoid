#ifndef KXM_VECTOID_VULKAN_CONTEXT_H_
#define KXM_VECTOID_VULKAN_CONTEXT_H_

namespace kxm {
namespace Vectoid {
namespace Vulkan {

//! Holds <c>Vulkan</c>-specific context for scene graph nodes.
/*!
 *  \ingroup VectoidVulkan
 */
struct Context {
    Context();
    Context(const Context &other) = delete;
    Context &operator=(const Context &other) = delete;
};

}    // Namespace Vulkan.
}    // Namespace Vectoid.
}    // Namespace kxm.

#endif    // KXM_VECTOID_VULKAN_CONTEXT_H_
