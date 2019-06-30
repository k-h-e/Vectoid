#include <kxm/Vectoid/Vulkan/Context.h>

#include <unordered_set>
#include <vulkan/vulkan.h>
#include <kxm/Core/logging.h>

using namespace std;

namespace kxm {
namespace Vectoid {
namespace Vulkan {

Context::Context() {
    instance = VK_NULL_HANDLE;
    
    vector<string> requiredExtensions;
    requiredExtensions.push_back("VK_MVK_macos_surface");
    requiredExtensions.push_back("harr");
    requiredExtensions.push_back("VK_KHR_swapchain");
    if (CreateInstance(requiredExtensions)) {
    
    }
}

bool Context::CreateInstance(const vector<string> &requiredExtensions) {
    uint32_t                      numExtensions;
    vector<VkExtensionProperties> extensionProperties;
    if (!vkEnumerateInstanceExtensionProperties(nullptr, &numExtensions, nullptr)) {
        extensionProperties.resize(numExtensions);
        if (!vkEnumerateInstanceExtensionProperties(nullptr, &numExtensions, &extensionProperties[0])) {
            unordered_set<string> availableExtensions;
            for (VkExtensionProperties &properties : extensionProperties) {
                availableExtensions.insert(properties.extensionName);
            }
            Core::Log().Stream() << "num_instance_extensions=" << availableExtensions.size() << endl;
            
            bool extensionsMissing = false;
            for (const string &extension : requiredExtensions) {
                if (availableExtensions.count(extension)) {
                     Core::Log().Stream() << "    " << extension << " present" << endl;
                }
                else {
                     Core::Log().Stream() << "    " << extension << " missing" << endl;
                     extensionsMissing = true;
                }
            }
            
            if (!extensionsMissing) {
                VkInstanceCreateInfo createInfo = {};
                
                // TODO...
                //createInfo. sdfgsdfg
                
            }
        }
    }
    return false;
}

}    // Namespace Vulkan.
}    // Namespace Vectoid.
}    // Namespace kxm.
