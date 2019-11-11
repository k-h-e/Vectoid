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
          swapChain(VK_NULL_HANDLE),
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
    if (!CreateSwapChain()) {
        Core::Log().Stream() << "failed to create swap chain" << endl;
        return;
    }
    if (!CreateDepthBuffer()) {
        Core::Log().Stream() << "failed to create depth buffer" << endl;
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
    FreeDepthBuffer();
    FreeSwapChain();
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
    
    if (vkCreateInstance(&instanceInfo, nullptr, &instance) != VK_SUCCESS) {
        return false;
    }

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
    
    if (vkCreateMacOSSurfaceMVK(instance, &info, nullptr, &surface) != VK_SUCCESS) {
        return false;
    }
    
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
    std::vector<VkPhysicalDevice> devices(deviceCount);
    if ((vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data()) != VK_SUCCESS)
            || (deviceCount == 0u)) {
        return false;
    }
    physicalDevice = devices[0];
    Core::Log().Stream() << "detected " << deviceCount << " physical devices" << endl;
    
    vkGetPhysicalDeviceMemoryProperties(physicalDevice, &physicalDeviceMemoryProperties);
    
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);
    if (queueFamilyCount == 0u) {
        return false;
    }
    vector<VkQueueFamilyProperties> queueFamilyProperties(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilyProperties.data());
    
    uint32_t graphicsQueueFamilyIndex = UINT32_MAX;
    uint32_t presentQueueFamilyIndex  = UINT32_MAX;
    vector<VkBool32> supportsPresent(queueFamilyCount);
    for (uint32_t i = 0; i < queueFamilyCount; i++) {
        if (vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, i, surface, &supportsPresent[i]) != VK_SUCCESS) {
            supportsPresent[i] = VK_FALSE;
        }
    }
    for (uint32_t i = 0u; i < queueFamilyCount; ++i) {
        if (queueFamilyProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            if (graphicsQueueFamilyIndex == UINT32_MAX) {
                graphicsQueueFamilyIndex = i;
            }
            if (supportsPresent[i] == VK_TRUE) {
                presentQueueFamilyIndex = i;
                break;
            }
        }
    }
    if (presentQueueFamilyIndex == UINT32_MAX) {
        for (uint32_t i = 0u; i < queueFamilyCount; ++i) {
            if (supportsPresent[i] == VK_TRUE) {
                presentQueueFamilyIndex = i;
                break;
            }
        }
    }
        
    if ((graphicsQueueFamilyIndex == UINT32_MAX) || (presentQueueFamilyIndex == UINT32_MAX)) {
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
    
    float graphicsPriorities[1] = { 0.0f };
    float presentPriorities[1]  = { 0.0f };
    VkDeviceQueueCreateInfo queueInfos[2];
    uint32_t numQueues = 0u;

    queueInfos[numQueues] = {};
    queueInfos[numQueues].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueInfos[numQueues].pNext = nullptr;
    queueInfos[numQueues].queueCount = 1;
    queueInfos[numQueues].queueFamilyIndex = graphicsQueueFamilyIndex;
    queueInfos[numQueues].pQueuePriorities = graphicsPriorities;
    ++numQueues;

    if (graphicsQueueFamilyIndex != presentQueueFamilyIndex) {
        queueInfos[numQueues] = {};
        queueInfos[numQueues].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueInfos[numQueues].pNext = nullptr;
        queueInfos[numQueues].queueCount = 1;
        queueInfos[numQueues].queueFamilyIndex = presentQueueFamilyIndex;
        queueInfos[numQueues].pQueuePriorities = presentPriorities;
        ++numQueues;
    }

    VkDeviceCreateInfo deviceInfo = {};
    deviceInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    deviceInfo.pNext = nullptr;
    deviceInfo.queueCreateInfoCount = numQueues;
    deviceInfo.pQueueCreateInfos = &queueInfos[0];
    deviceInfo.enabledExtensionCount = static_cast<uint32_t>(extensionNamePointers.size());
    deviceInfo.ppEnabledExtensionNames = extensionNamePointers.data();
    deviceInfo.enabledLayerCount = 0;
    deviceInfo.ppEnabledLayerNames = nullptr;
    deviceInfo.pEnabledFeatures = nullptr;
    
    if (vkCreateDevice(physicalDevice, &deviceInfo, nullptr, &device) != VK_SUCCESS) {
        return false;
    }
   
    Core::Log().Stream() << "device created, num_queues=" << numQueues << ", graphics_queue="
                         << graphicsQueueFamilyIndex << ", present_queue=" << presentQueueFamilyIndex << endl;
    return true;
}

void Context::FreeDevice() {
    if (device != VK_NULL_HANDLE) {
        Core::Log().Stream() << "freeing device" << endl;
        vkDestroyDevice(device, nullptr);
        device = VK_NULL_HANDLE;
    }
}

bool Context::CreateSwapChain() {
    uint32_t numFormats;
    if (vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &numFormats, nullptr) != VK_SUCCESS) {
        return false;
    }
    vector<VkSurfaceFormatKHR> formats(numFormats);
    if (vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &numFormats, formats.data()) != VK_SUCCESS) {
        return false;
    }
    VkFormat format;
    if ((numFormats == 1u) && (formats[0].format == VK_FORMAT_UNDEFINED)) {
        format = VK_FORMAT_B8G8R8A8_UNORM;
    } else if (numFormats >= 1u) {
        format = formats[0].format;
    } else {
        return false;
    }
    Core::Log().Stream() << "selected surface format " << format << endl;
    
    VkSurfaceCapabilitiesKHR capabilities;
    if (vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface, &capabilities) != VK_SUCCESS) {
        return false;
    }
    uint32_t numPresentModes;
    if (vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &numPresentModes, nullptr)
            != VK_SUCCESS) {
        return false;
    }
    vector<VkPresentModeKHR> presentModes(numPresentModes);
    if (vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &numPresentModes, presentModes.data())
            != VK_SUCCESS) {
        return false;
    }
    Core::Log().Stream() << "num_present_modes=" << numPresentModes << endl;
    
    if (capabilities.currentExtent.width == 0xffffffffu) {    // Surface size undefined.
        width  = 64u;
        height = 64u;
        if (width < capabilities.minImageExtent.width) {
            width = capabilities.minImageExtent.width;
        }
        if (width > capabilities.maxImageExtent.width) {
            width = capabilities.maxImageExtent.width;
        }

        if (height < capabilities.minImageExtent.height) {
            height = capabilities.minImageExtent.height;
        }
        if (height > capabilities.maxImageExtent.height) {
            height = capabilities.maxImageExtent.height;
        }
    } else {
        width  = capabilities.currentExtent.width;
        height = capabilities.currentExtent.height;
    }
    Core::Log().Stream() << "extent=" << width << "x" << height << endl;
    
    VkPresentModeKHR swapchainPresentMode = VK_PRESENT_MODE_FIFO_KHR;
    uint32_t desiredNumberOfSwapChainImages = capabilities.minImageCount;
    
    VkSurfaceTransformFlagBitsKHR preTransform;
    if (capabilities.supportedTransforms & VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR) {
        preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
    } else {
        preTransform = capabilities.currentTransform;
    }
    
    VkCompositeAlphaFlagBitsKHR compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    const int numCompositeAlphaFlags = 4;
    VkCompositeAlphaFlagBitsKHR compositeAlphaFlags[numCompositeAlphaFlags] = {
        VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
        VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR,
        VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR,
        VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR,
    };
    for (int i = 0; i < numCompositeAlphaFlags; ++i) {
        if (capabilities.supportedCompositeAlpha & compositeAlphaFlags[i]) {
            compositeAlpha = compositeAlphaFlags[i];
            break;
        }
    }
    
    VkSwapchainCreateInfoKHR swapChainInfo = {};
    swapChainInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    swapChainInfo.pNext = nullptr;
    swapChainInfo.surface = surface;
    swapChainInfo.minImageCount = desiredNumberOfSwapChainImages;
    swapChainInfo.imageFormat = format;
    swapChainInfo.imageExtent.width = width;
    swapChainInfo.imageExtent.height = height;
    swapChainInfo.preTransform = preTransform;
    swapChainInfo.compositeAlpha = compositeAlpha;
    swapChainInfo.imageArrayLayers = 1;
    swapChainInfo.presentMode = swapchainPresentMode;
    swapChainInfo.oldSwapchain = VK_NULL_HANDLE;
    swapChainInfo.clipped = true;
    swapChainInfo.imageColorSpace = VK_COLORSPACE_SRGB_NONLINEAR_KHR;
    swapChainInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    uint32_t queueFamilyIndices[2] = { graphicsQueueFamilyIndex, presentQueueFamilyIndex };
    if (graphicsQueueFamilyIndex != presentQueueFamilyIndex) {
        swapChainInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        swapChainInfo.queueFamilyIndexCount = 2;
        swapChainInfo.pQueueFamilyIndices = queueFamilyIndices;
    }
    else {
        swapChainInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        swapChainInfo.queueFamilyIndexCount = 0;
        swapChainInfo.pQueueFamilyIndices = nullptr;
    }
    
    if (vkCreateSwapchainKHR(device, &swapChainInfo, nullptr, &swapChain) != VK_SUCCESS) {
        return false;
    }
    
    uint32_t numImages;
    if (vkGetSwapchainImagesKHR(device, swapChain, &numImages, nullptr) != VK_SUCCESS) {
        return false;
    }
    vector<VkImage> images(numImages);
    if (vkGetSwapchainImagesKHR(device, swapChain, &numImages, images.data()) != VK_SUCCESS) {
        return false;
    }
    colorBuffers.clear();
    for (uint32_t i = 0u; i < numImages; ++i) {
        BufferInfo info;
        info.image = images[i];
        colorBuffers.push_back(info);
    }

    for (uint32_t i = 0; i < numImages; ++i) {
        VkImageViewCreateInfo imageViewInfo = {};
        imageViewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        imageViewInfo.pNext = nullptr;
        imageViewInfo.flags = 0;
        imageViewInfo.image = colorBuffers[i].image;
        imageViewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        imageViewInfo.format = format;
        imageViewInfo.components.r = VK_COMPONENT_SWIZZLE_R;
        imageViewInfo.components.g = VK_COMPONENT_SWIZZLE_G;
        imageViewInfo.components.b = VK_COMPONENT_SWIZZLE_B;
        imageViewInfo.components.a = VK_COMPONENT_SWIZZLE_A;
        imageViewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        imageViewInfo.subresourceRange.baseMipLevel = 0;
        imageViewInfo.subresourceRange.levelCount = 1;
        imageViewInfo.subresourceRange.baseArrayLayer = 0;
        imageViewInfo.subresourceRange.layerCount = 1;

        if (vkCreateImageView(device, &imageViewInfo, nullptr, &colorBuffers[i].view) != VK_SUCCESS) {
            return false;
        }
    }

    Core::Log().Stream() << "swap chain created" << endl;
    return true;
}

void Context::FreeSwapChain() {
    for (BufferInfo &info : colorBuffers) {
        if (info.view != VK_NULL_HANDLE) {
            Core::Log().Stream() << "deleting image view" << endl;
            vkDestroyImageView(device, info.view, nullptr);
            info.view = VK_NULL_HANDLE;
        }
    }
    colorBuffers.clear();

    if (swapChain != VK_NULL_HANDLE) {
        Core::Log().Stream() << "deleting swap chain" << endl;
        vkDestroySwapchainKHR(device, swapChain, nullptr);
        swapChain = VK_NULL_HANDLE;
    }
}

bool Context::CreateDepthBuffer() {
    const VkFormat format = VK_FORMAT_D16_UNORM;
    VkImageTiling tiling;
    VkFormatProperties properties;
    vkGetPhysicalDeviceFormatProperties(physicalDevice, format, &properties);
    if (properties.linearTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) {
        tiling = VK_IMAGE_TILING_LINEAR;
    }
    else if (properties.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) {
        tiling = VK_IMAGE_TILING_OPTIMAL;
    } else {
        return false;
    }
    Core::Log().Stream() << "have tiling" << endl;

    VkImageCreateInfo imageInfo = {};
    imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    imageInfo.pNext = nullptr;
    imageInfo.imageType = VK_IMAGE_TYPE_2D;
    imageInfo.format = format;
    imageInfo.extent.width = width;
    imageInfo.extent.height = height;
    imageInfo.extent.depth = 1;
    imageInfo.mipLevels = 1;
    imageInfo.arrayLayers = 1;
    imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
    imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    imageInfo.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
    imageInfo.queueFamilyIndexCount = 0;
    imageInfo.pQueueFamilyIndices = nullptr;
    imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    imageInfo.flags = 0;
    if (vkCreateImage(device, &imageInfo, nullptr, &depthBuffer.image) != VK_SUCCESS) {
        return false;
    }
    
    VkMemoryRequirements memoryRequirements;
    vkGetImageMemoryRequirements(device, depthBuffer.image, &memoryRequirements);
    VkMemoryAllocateInfo memoryInfo = {};
    memoryInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    memoryInfo.pNext = nullptr;
    memoryInfo.allocationSize = memoryRequirements.size;
    memoryInfo.memoryTypeIndex = 0;
    if (!checkMemoryType(memoryRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
                        &memoryInfo.memoryTypeIndex)) {
        return false;
    }
    if (vkAllocateMemory(device, &memoryInfo, nullptr, &depthBuffer.memory) != VK_SUCCESS) {
        return false;
    }
    if (vkBindImageMemory(device, depthBuffer.image, depthBuffer.memory, 0) != VK_SUCCESS) {
        return false;
    }

    VkImageViewCreateInfo viewInfo = {};
    viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    viewInfo.pNext = nullptr;
    viewInfo.image = depthBuffer.image;
    viewInfo.format = format;
    viewInfo.components.r = VK_COMPONENT_SWIZZLE_R;
    viewInfo.components.g = VK_COMPONENT_SWIZZLE_G;
    viewInfo.components.b = VK_COMPONENT_SWIZZLE_B;
    viewInfo.components.a = VK_COMPONENT_SWIZZLE_A;
    viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
    viewInfo.subresourceRange.baseMipLevel = 0;
    viewInfo.subresourceRange.levelCount = 1;
    viewInfo.subresourceRange.baseArrayLayer = 0;
    viewInfo.subresourceRange.layerCount = 1;
    viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
    viewInfo.flags = 0;
    if (vkCreateImageView(device, &viewInfo, nullptr, &depthBuffer.view) != VK_SUCCESS) {
        return false;
    }
    
    Core::Log().Stream() << "depth buffer created" << endl;
    return true;
}

void Context::FreeDepthBuffer() {
    if (depthBuffer.view != VK_NULL_HANDLE) {
        Core::Log().Stream() << "freeing depth buffer view" << endl;
        vkDestroyImageView(device, depthBuffer.view, nullptr);
        depthBuffer.view = VK_NULL_HANDLE;
    }
    if (depthBuffer.image != VK_NULL_HANDLE) {
        Core::Log().Stream() << "freeing depth buffer image" << endl;
        vkDestroyImage(device, depthBuffer.image, nullptr);
        depthBuffer.image = VK_NULL_HANDLE;
    }
    if (depthBuffer.memory != VK_NULL_HANDLE) {
        Core::Log().Stream() << "freeing depth buffer memory" << endl;
        vkFreeMemory(device, depthBuffer.memory, nullptr);
        depthBuffer.memory = VK_NULL_HANDLE;
    }
}

bool Context::CreateCommandBufferPool() {
    VkCommandPoolCreateInfo info = {};
    info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    info.pNext = nullptr;
    info.queueFamilyIndex = graphicsQueueFamilyIndex;
    info.flags = 0;
    
    if (vkCreateCommandPool(device, &info, nullptr, &commandBufferPool) != VK_SUCCESS) {
        return false;
    }
    
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
    VkCommandBufferAllocateInfo info = {};
    info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    info.pNext = nullptr;
    info.commandPool = commandBufferPool;
    info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    info.commandBufferCount = 1;
    if (vkAllocateCommandBuffers(device, &info, &commandBuffer) != VK_SUCCESS) {
        return false;
    }

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

bool Context::checkMemoryType(uint32_t typeBits, VkFlags requirementsMask, uint32_t *typeIndex) {
    for (uint32_t i = 0u; i < physicalDeviceMemoryProperties.memoryTypeCount; ++i) {
        if ((typeBits & 1u) == 1u) {
            if ((physicalDeviceMemoryProperties.memoryTypes[i].propertyFlags & requirementsMask) == requirementsMask) {
                *typeIndex = i;
                return true;
            }
        }
        typeBits >>= 1;
    }

    return false;
}

}    // Namespace Vulkan.
}    // Namespace Vectoid.
}    // Namespace kxm.
