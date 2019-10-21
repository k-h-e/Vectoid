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
          queueFamilyCount(0u),
          graphicsQueueFamilyIndex(0u),
          presentQueueFamilyIndex(0u),
          commandBufferPool(VK_NULL_HANDLE),
          commandBuffer(VK_NULL_HANDLE),
          operative_(false) {
    if (!CreateInstance()) {
        Core::Log().Stream() << "failed to create instance" << endl;
        return;
    }
    if (!CreateSurface(view)) {
        Core::Log().Stream() << "failed to create surface" << endl;
        return;
    }
    if (!CreateDevice()) {
        Core::Log().Stream() << "failed to create device" << endl;
        return;
    }
    if (!CreateCommandBufferPool()) {
        Core::Log().Stream() << "failed to create command buffer pool" << endl;
        return;
    }
    
    operative_ = true;
}

Context::~Context() {
    FreeCommandBuffer();
    FreeCommandBufferPool();
    FreeDevice();
    FreeSurface();
    FreeInstance();
}

bool Context::Operative() {
    return operative_;
}

bool Context::CreateInstance() {
    vector<string> requiredExtensions;
    requiredExtensions.push_back("VK_MVK_macos_surface");

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
            Core::Log().Stream() << "will request instance extension " << extension << endl;
        }
        else {
            Core::Log().Stream() << "instance extension " << extension << " missing" << endl;
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
    Core::Log().Stream() << "instance created" << endl;
    return true;
}

void Context::FreeInstance() {
    if (instance != VK_NULL_HANDLE) {
        Core::Log().Stream() << "deleting instance" << endl;
        vkDestroyInstance(instance, nullptr);
        instance = VK_NULL_HANDLE;
    }
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
    Core::Log().Stream() << "surface created" << endl;
    return true;
}

void Context::FreeSurface() {
    if (surface != VK_NULL_HANDLE) {
        Core::Log().Stream() << "deleting surface" << endl;
        vkDestroySurfaceKHR(instance, surface, nullptr);
        surface = VK_NULL_HANDLE;
    }
}

bool Context::CreateDevice() {
    vector<string> requiredExtensions;
    requiredExtensions.push_back("VK_KHR_swapchain");

    uint32_t deviceCount;
    if ((vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr) != VK_SUCCESS) || (deviceCount == 0u)) {
        return false;
    }
    vector<VkPhysicalDevice> devices(deviceCount);
    if ((vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data()) != VK_SUCCESS) || (deviceCount == 0u)) {
        return false;
    }
    Core::Log().Stream() << "detected " << deviceCount << " physical devices" << endl;
    
    uint32_t aQueueFamilyCount;
    vkGetPhysicalDeviceQueueFamilyProperties(devices[0], &aQueueFamilyCount, nullptr);
    if (aQueueFamilyCount == 0u) {
        return false;
    }
    vector<VkQueueFamilyProperties> queueFamilyProperties(aQueueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(devices[0], &aQueueFamilyCount, queueFamilyProperties.data());
    
    uint32_t aGraphicsQueueFamilyIndex = UINT32_MAX;
    uint32_t aPresentQueueFamilyIndex  = UINT32_MAX;
    VkBool32 *supportsPresent = (VkBool32 *)malloc(aQueueFamilyCount * sizeof(VkBool32));
    if (supportsPresent) {
        for (uint32_t i = 0; i < aQueueFamilyCount; i++) {
            if (vkGetPhysicalDeviceSurfaceSupportKHR(devices[0], i, surface, &supportsPresent[i]) != VK_SUCCESS) {
                supportsPresent[i] = VK_FALSE;
            }
        }
        for (uint32_t i = 0u; i < aQueueFamilyCount; ++i) {
            if (queueFamilyProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                if (aGraphicsQueueFamilyIndex == UINT32_MAX) {
                    aGraphicsQueueFamilyIndex = i;
                }
                if (supportsPresent[i] == VK_TRUE) {
                    aPresentQueueFamilyIndex = i;
                    break;
                }
            }
        }
        if (aPresentQueueFamilyIndex == UINT32_MAX) {
            for (uint32_t i = 0u; i < aQueueFamilyCount; ++i) {
                if (supportsPresent[i] == VK_TRUE) {
                    aPresentQueueFamilyIndex = i;
                    break;
                }
            }
        }
        
        free(supportsPresent);
    }
    if ((aGraphicsQueueFamilyIndex == UINT32_MAX) || (aPresentQueueFamilyIndex == UINT32_MAX)) {
        return false;
    }
    
    vector<string> extensionNames;    // Don't want to modifiy state of passed-in vector.
    for (const string &extension : requiredExtensions) {
        extensionNames.push_back(extension);
        Core::Log().Stream() << "will request device extension " << extension << endl;
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
    queueInfo.queueFamilyIndex = aGraphicsQueueFamilyIndex;
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
    
    device                   = aDevice;
    queueFamilyCount         = aQueueFamilyCount;
    graphicsQueueFamilyIndex = aGraphicsQueueFamilyIndex;
    presentQueueFamilyIndex  = aPresentQueueFamilyIndex;
    Core::Log().Stream() << "device created, graphics_queue=" << graphicsQueueFamilyIndex << ", present_queue="
                         << presentQueueFamilyIndex << endl;
    return true;
}

void Context::FreeDevice() {
    if (device != VK_NULL_HANDLE) {
        Core::Log().Stream() << "freeing device" << endl;
        vkDestroyDevice(device, nullptr);
        device = VK_NULL_HANDLE;
    }
}

bool Context::CreateCommandBufferPool() {
    VkCommandPoolCreateInfo info = {};
    info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    info.pNext = nullptr;
    info.queueFamilyIndex = graphicsQueueFamilyIndex;
    info.flags = 0;
    
    VkCommandPool aCommandBufferPool;
    if (vkCreateCommandPool(device, &info, nullptr, &aCommandBufferPool) != VK_SUCCESS) {
        return false;
    }
    
    commandBufferPool = aCommandBufferPool;
    Core::Log().Stream() << "command buffer pool created" << endl;
    return true;
}

void Context::FreeCommandBufferPool() {
   if (commandBufferPool != VK_NULL_HANDLE) {
       Core::Log().Stream() << "freeing command buffer pool" << endl;
       vkDestroyCommandPool(device, commandBufferPool, nullptr);
       commandBufferPool = VK_NULL_HANDLE;
   }
}

bool Context::CreateCommandBuffer() {
    if ((commandBuffer != VK_NULL_HANDLE) || (device == VK_NULL_HANDLE) || (commandBufferPool == VK_NULL_HANDLE)) {
        return false;
    }

    VkCommandBufferAllocateInfo info = {};
    info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    info.pNext = NULL;
    info.commandPool = commandBufferPool;
    info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    info.commandBufferCount = 1;
    VkCommandBuffer aCommandBuffer;
    if (vkAllocateCommandBuffers(device, &info, &aCommandBuffer) != VK_SUCCESS) {
        return false;
    }
    
    commandBuffer = aCommandBuffer;
    Core::Log().Stream() << "command buffer created" << endl;
    return true;
}

void Context::FreeCommandBuffer() {
    if (commandBuffer != VK_NULL_HANDLE) {
        Core::Log().Stream() << "freeing command buffer" << endl;
        vkFreeCommandBuffers(device, commandBufferPool, 1, &commandBuffer);
        commandBuffer = VK_NULL_HANDLE;
    }
}

}    // Namespace Vulkan.
}    // Namespace Vectoid.
}    // Namespace kxm.
