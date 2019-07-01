#include <kxm/Vectoid/Vulkan/Context.h>

#include <unordered_set>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_macos.h>
#include <kxm/Core/logging.h>

using namespace std;

namespace kxm {
namespace Vectoid {
namespace Vulkan {

Context::Context(void *view)
        : instance(VK_NULL_HANDLE),
          surface(VK_NULL_HANDLE),
          device(VK_NULL_HANDLE),
          queueFamilyIndex(0u),
          commandBufferPool(VK_NULL_HANDLE),
          commandBuffer(VK_NULL_HANDLE),
          operative_(false) {
    vector<string> extensions;
    extensions.push_back("VK_MVK_macos_surface");
    extensions.push_back("VK_KHR_swapchain");
    if (!CreateInstance(extensions)) {
        Core::Log().Stream() << "failed to create Vulkan instance" << endl;
        return;
    }
    
    if (!CreateSurface(view)) {
        Core::Log().Stream() << "failed to create Vulkan surface" << endl;
        return;
    }
    
    extensions.clear();
    extensions.push_back("VK_KHR_swapchain");
    if (!CreateDevice(extensions)) {
        Core::Log().Stream() << "failed to create Vulkan device" << endl;
        return;
    }
    
    if (!CreateCommandBufferPool()) {
        Core::Log().Stream() << "failed to create Vulkan command buffer pool" << endl;
        return;
    }
    
    operative_ = true;
}

Context::~Context() {
    if (commandBufferPool != VK_NULL_HANDLE) {
        Core::Log().Stream() << "deleting Vulkan command buffer pool" << endl;
        vkDestroyCommandPool(device, commandBufferPool, nullptr);
    }
    if (device != VK_NULL_HANDLE) {
        Core::Log().Stream() << "deleting Vulkan device" << endl;
        vkDestroyDevice(device, nullptr);
    }
    if (surface != VK_NULL_HANDLE) {
        Core::Log().Stream() << "deleting Vulkan surface" << endl;
        vkDestroySurfaceKHR(instance, surface, nullptr);
    }
    if (instance != VK_NULL_HANDLE) {
        Core::Log().Stream() << "deleting Vulkan instance" << endl;
        vkDestroyInstance(instance, nullptr);
    }
}

bool Context::Operative() {
    return operative_;
}

bool Context::CreateInstance(const vector<string> &requiredExtensions) {
    uint32_t numExtensions;
    if (vkEnumerateInstanceExtensionProperties(nullptr, &numExtensions, nullptr) != VK_SUCCESS) {
        return false;
    }
    
    vector<VkExtensionProperties> extensionProperties(numExtensions);
    if (vkEnumerateInstanceExtensionProperties(nullptr, &numExtensions, extensionProperties.data()) != VK_SUCCESS) {
        return false;
    }
    unordered_set<string> availableExtensions;
    for (VkExtensionProperties &properties : extensionProperties) {
        availableExtensions.insert(properties.extensionName);
    }
    
    vector<string> extensionNames;    // Don't want to modifiy state of passed-in vector.
    for (const string &extension : requiredExtensions) {
        if (availableExtensions.find(extension) != availableExtensions.end()) {
            extensionNames.push_back(extension);
            Core::Log().Stream() << "will request Vulkan instance extension " << extension << endl;
        }
        else {
            Core::Log().Stream() << "Vulkan instance extension " << extension << " missing" << endl;
            return false;
        }
    }
    vector<const char *> extensionNamePointers;
    for (const string &extensionName : extensionNames) {
        extensionNamePointers.push_back(extensionName.c_str());
    }
    
    VkApplicationInfo appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pNext = nullptr;
    appInfo.pApplicationName = "Vectoid";
    appInfo.applicationVersion = 1;
    appInfo.pEngineName = "Vectoid";
    appInfo.engineVersion = 1;
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo instanceInfo = {};
    instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instanceInfo.pNext = nullptr;
    instanceInfo.flags = 0;
    instanceInfo.pApplicationInfo = &appInfo;
    instanceInfo.enabledExtensionCount = static_cast<uint32_t>(extensionNamePointers.size());
    instanceInfo.ppEnabledExtensionNames = extensionNamePointers.data();
    instanceInfo.enabledLayerCount = 0;
    instanceInfo.ppEnabledLayerNames = nullptr;
    
    VkInstance anInstance;
    if (vkCreateInstance(&instanceInfo, nullptr, &anInstance) != VK_SUCCESS) {
        return false;
    }

    instance = anInstance;
    Core::Log().Stream() << "Vulkan instance created" << endl;
    return true;
}

bool Context::CreateSurface(void *view) {
    VkMacOSSurfaceCreateInfoMVK info = {};
    info.sType = VK_STRUCTURE_TYPE_MACOS_SURFACE_CREATE_INFO_MVK;
    info.pNext = nullptr;
    info.flags = 0;
    info.pView = view;
    
    VkSurfaceKHR aSurface;
    if (vkCreateMacOSSurfaceMVK(instance, &info, nullptr, &aSurface) != VK_SUCCESS) {
        return false;
    }
    
    surface = aSurface;
    Core::Log().Stream() << "Vulkan surface created" << endl;
    return true;
}

bool Context::CreateDevice(const std::vector<std::string> &requiredExtensions) {
    uint32_t deviceCount;
    if ((vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr) != VK_SUCCESS) || (deviceCount == 0u)) {
        return false;
    }
    vector<VkPhysicalDevice> devices(deviceCount);
    if ((vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data()) != VK_SUCCESS) || (deviceCount == 0u)) {
        return false;
    }
    Core::Log().Stream() << "detected " << deviceCount << " physical Vulkan devices" << endl;
    
    uint32_t queueFamilyCount;
    vkGetPhysicalDeviceQueueFamilyProperties(devices[0], &queueFamilyCount, nullptr);
    if (queueFamilyCount == 0u) {
        return false;
    }
    vector<VkQueueFamilyProperties> queueFamilyProperties(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(devices[0], &queueFamilyCount, queueFamilyProperties.data());
    
    bool     didSelectQueueFamily = false;
    uint32_t selectedQueueFamilyIndex;
    for (uint32_t i = 0u; i < queueFamilyCount; ++i) {
        if (queueFamilyProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            selectedQueueFamilyIndex = i;
            didSelectQueueFamily     = true;
        }
    }
    if (!didSelectQueueFamily) {
        return false;
    }
    
    vector<string> extensionNames;    // Don't want to modifiy state of passed-in vector.
    for (const string &extension : requiredExtensions) {
        extensionNames.push_back(extension);
        Core::Log().Stream() << "will request Vulkan device extension " << extension << endl;
    }
    vector<const char *> extensionNamePointers;
    for (const string &extensionName : extensionNames) {
        extensionNamePointers.push_back(extensionName.c_str());
    }
    
    float queuePriorities[1] = {0.0};
    VkDeviceQueueCreateInfo queueInfo = {};
    queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueInfo.pNext = nullptr;
    queueInfo.queueCount = 1;
    queueInfo.queueFamilyIndex = selectedQueueFamilyIndex;
    queueInfo.pQueuePriorities = queuePriorities;
    
    VkDeviceCreateInfo deviceInfo = {};
    deviceInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    deviceInfo.pNext = nullptr;
    deviceInfo.queueCreateInfoCount = 1;
    deviceInfo.pQueueCreateInfos = &queueInfo;
    deviceInfo.enabledExtensionCount = static_cast<uint32_t>(extensionNamePointers.size());
    deviceInfo.ppEnabledExtensionNames = extensionNamePointers.data();
    deviceInfo.enabledLayerCount = 0;
    deviceInfo.ppEnabledLayerNames = nullptr;
    deviceInfo.pEnabledFeatures = nullptr;
    
    VkDevice aDevice;
    if (vkCreateDevice(devices[0], &deviceInfo, nullptr, &aDevice) != VK_SUCCESS) {
        return false;
    }
    
    device           = aDevice;
    queueFamilyIndex = selectedQueueFamilyIndex;
    Core::Log().Stream() << "Vulkan device created" << endl;
    return true;
}

bool Context::CreateCommandBufferPool() {
    VkCommandPoolCreateInfo info = {};
    info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    info.pNext = nullptr;
    info.queueFamilyIndex = queueFamilyIndex;
    info.flags = 0;
    
    VkCommandPool aCommandBufferPool;
    if (vkCreateCommandPool(device, &info, nullptr, &aCommandBufferPool) != VK_SUCCESS) {
        return false;
    }
    
    commandBufferPool = aCommandBufferPool;
    Core::Log().Stream() << "Vulkan command buffer pool created" << endl;
    return true;
}

}    // Namespace Vulkan.
}    // Namespace Vectoid.
}    // Namespace kxm.
