///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//                                           //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/SceneGraph/Vulkan/Context.h>

#include <unordered_set>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_macos.h>
#include <MoltenVKGLSLToSPIRVConverter/GLSLToSPIRVConverter.h>
#include <K/Core/Log.h>

using namespace std;
using K::Core::Log;

namespace Vectoid {
namespace SceneGraph {
namespace Vulkan {

Context::Context(void *view)
        : instance(VK_NULL_HANDLE),
          surface(VK_NULL_HANDLE),
          device(VK_NULL_HANDLE),
          queueFamilyCount(0u),
          graphicsQueueFamilyIndex(0u),
          presentQueueFamilyIndex(0u),
          graphicsQueue(VK_NULL_HANDLE),
          presentQueue(VK_NULL_HANDLE),
          swapChain(VK_NULL_HANDLE),
          width(0u),
          height(0u),
          currentBuffer(0u),
          pipelineLayout(VK_NULL_HANDLE),
          imageAcquiredSemaphore(VK_NULL_HANDLE),
          drawFence(VK_NULL_HANDLE),
          renderPass(VK_NULL_HANDLE),
          vertexShader(VK_NULL_HANDLE),
          fragmentShader(VK_NULL_HANDLE),
          pipeline(VK_NULL_HANDLE),
          commandBufferPool(VK_NULL_HANDLE),
          commandBuffer(VK_NULL_HANDLE),
          operative_(false),
          currentObjectTransformChanged_(true) {
    if (!CreateInstance()) {
        Log::Print(Log::Level::Debug, nullptr, []{ return "failed to create instance"; });
        return;
    }
    if (!CreateSurface(view)) {
        Log::Print(Log::Level::Debug, nullptr, []{ return "failed to create surface"; });
        return;
    }
    if (!CreateDevice()) {
        Log::Print(Log::Level::Debug, nullptr, []{ return "failed to create device"; });
        return;
    }
    if (!CreateSwapChain()) {
        Log::Print(Log::Level::Debug, nullptr, []{ return "failed to create swap chain"; });
        return;
    }
    if (!CreateDepthBuffer()) {
        Log::Print(Log::Level::Debug, nullptr, []{ return "failed to create depth buffer"; });
        return;
    }
    if (!CreateLayouts()) {
        Log::Print(Log::Level::Debug, nullptr, []{ return "failed to create layouts"; });
        return;
    }
    if (!CreateRenderPass()) {
        Log::Print(Log::Level::Debug, nullptr, []{ return "failed to create render pass"; });
        return;
    }
    if (!CreateShaders()) {
        Log::Print(Log::Level::Debug, nullptr, []{ return "failed to create shaders"; });
        return;
    }
    if (!CreateFrameBuffers()) {
        Log::Print(Log::Level::Debug, nullptr, []{ return "failed to create frame buffers"; });
        return;
    }
    if (!CreatePipeline()) {
        Log::Print(Log::Level::Debug, nullptr, []{ return "failed to create pipeline"; });
        return;
    }
    if (!CreateCommandBufferPool()) {
        Log::Print(Log::Level::Debug, nullptr, []{ return "failed to create command buffer pool"; });
        return;
    }
    
    operative_ = true;
}

Context::~Context() {
    FreeCommandBuffer();
    FreeCommandBufferPool();
    FreePipeline();
    FreeFrameBuffers();
    FreeShaders();
    FreeRenderPass();
    FreeLayouts();
    FreeDepthBuffer();
    FreeSwapChain();
    FreeDevice();
    FreeSurface();
    FreeInstance();
}

bool Context::Operative() {
    return operative_;
}

void Context::UpdateObjectTransform(const Core::FullTransform &transform) {
    currentObjectTransform_        = transform;
    currentObjectTransformChanged_ = true;
}

void Context::ApplyObjectTransform() {
    if (currentObjectTransformChanged_) {
        vkCmdPushConstants(commandBuffer, pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT, 0,
                           currentObjectTransform_.MatrixSize(), currentObjectTransform_.MatrixElements());
        currentObjectTransformChanged_ = false;
    }
}

const Core::FullTransform &Context::ObjectTransform() {
    return currentObjectTransform_;
}

bool Context::GetMemoryIndex(uint32_t typeBits, VkFlags requirementsMask, uint32_t *typeIndex) {
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

void Context::RecoverFromOutOfDateImage() {
    FreeCommandBuffer();
    FreeCommandBufferPool();
    FreePipeline();
    FreeFrameBuffers();
    FreeShaders();
    FreeRenderPass();
    FreeLayouts();
    FreeDepthBuffer();
    FreeSwapChain();
    
    operative_ = false;
    
    if (!CreateSwapChain()) {
        Log::Print(Log::Level::Debug, nullptr, []{ return "failed to create swap chain"; });
        return;
    }
    if (!CreateDepthBuffer()) {
        Log::Print(Log::Level::Debug, nullptr, []{ return "failed to create depth buffer"; });
        return;
    }
    if (!CreateLayouts()) {
        Log::Print(Log::Level::Debug, nullptr, []{ return "failed to create layouts"; });
        return;
    }
    if (!CreateRenderPass()) {
        Log::Print(Log::Level::Debug, nullptr, []{ return "failed to create render pass"; });
        return;
    }
    if (!CreateShaders()) {
        Log::Print(Log::Level::Debug, nullptr, []{ return "failed to create shaders"; });
        return;
    }
    if (!CreateFrameBuffers()) {
        Log::Print(Log::Level::Debug, nullptr, []{ return "failed to create frame buffers"; });
        return;
    }
    if (!CreatePipeline()) {
        Log::Print(Log::Level::Debug, nullptr, []{ return "failed to create pipeline"; });
        return;
    }
    if (!CreateCommandBufferPool()) {
        Log::Print(Log::Level::Debug, nullptr, []{ return "failed to create command buffer pool"; });
        return;
    }
    
    operative_ = true;
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
            Log::Print(Log::Level::Debug, nullptr, [&]{ return "will request instance extension " + extension; });
        }
        else {
            Log::Print(Log::Level::Debug, nullptr, [&]{ return "instance extension " + extension + " missing"; });
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

    Log::Print(Log::Level::Debug, nullptr, []{ return "instance created"; });
    return true;
}

void Context::FreeInstance() {
    if (instance != VK_NULL_HANDLE) {
        Log::Print(Log::Level::Debug, nullptr, []{ return "deleting instance"; });
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
    
    Log::Print(Log::Level::Debug, nullptr, []{ return "surface created"; });
    return true;
}

void Context::FreeSurface() {
    if (surface != VK_NULL_HANDLE) {
        Log::Print(Log::Level::Debug, nullptr, []{ return "deleting surface"; });
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
    Log::Print(Log::Level::Debug, nullptr, [&]{ return "detected " + to_string(deviceCount) + " physical devices"; });
    
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
        Log::Print(Log::Level::Debug, nullptr, [&]{ return "will request device extension " + extension; });
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
   
    vkGetDeviceQueue(device, graphicsQueueFamilyIndex, 0, &graphicsQueue);
    vkGetDeviceQueue(device, presentQueueFamilyIndex, 0, &presentQueue);
   
    Log::Print(Log::Level::Debug, nullptr, [&]{
        return "device created, num_queues=" + to_string(numQueues) + ", graphics_queue=" +
               to_string(graphicsQueueFamilyIndex) + ", present_queue=" + to_string(presentQueueFamilyIndex);
    });
    return true;
}

void Context::FreeDevice() {
    if (device != VK_NULL_HANDLE) {
        Log::Print(Log::Level::Debug, nullptr, []{ return "freeing device"; });
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
    if ((numFormats == 1u) && (formats[0].format == VK_FORMAT_UNDEFINED)) {
        colorFormat = VK_FORMAT_B8G8R8A8_UNORM;
    } else if (numFormats >= 1u) {
        colorFormat = formats[0].format;
    } else {
        return false;
    }
    Log::Print(Log::Level::Debug, nullptr, [&]{ return "selected surface format " + to_string(colorFormat); });
    
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
    Log::Print(Log::Level::Debug, nullptr, [&]{ return "num_present_modes=" + to_string(numPresentModes); });
    
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
    Log::Print(Log::Level::Debug, nullptr, [&]{ return "extent=" + to_string(width) + "x" + to_string(height); });
    
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
    swapChainInfo.imageFormat = colorFormat;
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
        FrameBufferInfo info;
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
        imageViewInfo.format = colorFormat;
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

    Log::Print(Log::Level::Debug, nullptr, [&]{
        return "swap chain created, num_images=" + to_string(colorBuffers.size());
    });
    return true;
}

void Context::FreeSwapChain() {
    for (FrameBufferInfo &info : colorBuffers) {
        if (info.view != VK_NULL_HANDLE) {
            Log::Print(Log::Level::Debug, nullptr, []{ return "deleting image view"; });
            vkDestroyImageView(device, info.view, nullptr);
            info.view = VK_NULL_HANDLE;
        }
    }
    colorBuffers.clear();

    if (swapChain != VK_NULL_HANDLE) {
        Log::Print(Log::Level::Debug, nullptr, []{ return "deleting swap chain"; });
        vkDestroySwapchainKHR(device, swapChain, nullptr);
        swapChain = VK_NULL_HANDLE;
    }
}

bool Context::CreateDepthBuffer() {
    depthFormat = VK_FORMAT_D16_UNORM;
    VkImageTiling tiling;
    VkFormatProperties properties;
    vkGetPhysicalDeviceFormatProperties(physicalDevice, depthFormat, &properties);
    if (properties.linearTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) {
        tiling = VK_IMAGE_TILING_LINEAR;
    }
    else if (properties.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) {
        tiling = VK_IMAGE_TILING_OPTIMAL;
    } else {
        return false;
    }
    Log::Print(Log::Level::Debug, nullptr, []{ return "have tiling"; });

    VkImageCreateInfo imageInfo = {};
    imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    imageInfo.pNext = nullptr;
    imageInfo.imageType = VK_IMAGE_TYPE_2D;
    imageInfo.format = depthFormat;
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
    if (!GetMemoryIndex(memoryRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
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
    viewInfo.format = depthFormat;
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
    
    Log::Print(Log::Level::Debug, nullptr, []{ return "depth buffer created"; });
    return true;
}

void Context::FreeDepthBuffer() {
    if (depthBuffer.view != VK_NULL_HANDLE) {
        Log::Print(Log::Level::Debug, nullptr, []{ return "freeing depth buffer view"; });
        vkDestroyImageView(device, depthBuffer.view, nullptr);
        depthBuffer.view = VK_NULL_HANDLE;
    }
    if (depthBuffer.image != VK_NULL_HANDLE) {
        Log::Print(Log::Level::Debug, nullptr, []{ return "freeing depth buffer image"; });
        vkDestroyImage(device, depthBuffer.image, nullptr);
        depthBuffer.image = VK_NULL_HANDLE;
    }
    if (depthBuffer.memory != VK_NULL_HANDLE) {
        Log::Print(Log::Level::Debug, nullptr, []{ return "freeing depth buffer memory"; });
        vkFreeMemory(device, depthBuffer.memory, nullptr);
        depthBuffer.memory = VK_NULL_HANDLE;
    }
}


bool Context::CreateLayouts() {
    VkPushConstantRange pushConstantRange = {};
    pushConstantRange.offset = 0;
    pushConstantRange.size = currentObjectTransform_.MatrixSize();
    pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

    VkPipelineLayoutCreateInfo pipelineInfo = {};
    pipelineInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineInfo.pNext = nullptr;
    pipelineInfo.pushConstantRangeCount = 1;
    pipelineInfo.pPushConstantRanges = &pushConstantRange;
    pipelineInfo.setLayoutCount = 0;
    pipelineInfo.pSetLayouts = nullptr;
    if (vkCreatePipelineLayout(device, &pipelineInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
        return false;
    }
    
    Log::Print(Log::Level::Debug, nullptr, []{ return "layouts created"; });
    return true;
}

void Context::FreeLayouts() {
    if (pipelineLayout != VK_NULL_HANDLE) {
        Log::Print(Log::Level::Debug, nullptr, []{ return "freeing pipeline layout"; });
        vkDestroyPipelineLayout(device, pipelineLayout, nullptr);
        pipelineLayout = VK_NULL_HANDLE;
    }
}

bool Context::CreateRenderPass() {
    VkSemaphoreCreateInfo semaphoreInfo = {};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
    semaphoreInfo.pNext = nullptr;
    semaphoreInfo.flags = 0;
    if (vkCreateSemaphore(device, &semaphoreInfo, nullptr, &imageAcquiredSemaphore) != VK_SUCCESS) {
        return false;
    }

    VkFenceCreateInfo fenceInfo = {};
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.pNext = nullptr;
    fenceInfo.flags = 0;
    if (vkCreateFence(device, &fenceInfo, nullptr, &drawFence) != VK_SUCCESS) {
        return false;
    }

    VkAttachmentDescription attachments[2];
    attachments[0].format = colorFormat;
    attachments[0].samples = VK_SAMPLE_COUNT_1_BIT;
    attachments[0].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    attachments[0].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    attachments[0].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    attachments[0].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    attachments[0].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    attachments[0].finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
    attachments[0].flags = 0;
    
    attachments[1].format = depthFormat;
    attachments[1].samples = VK_SAMPLE_COUNT_1_BIT;
    attachments[1].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    attachments[1].storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    attachments[1].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    attachments[1].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    attachments[1].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    attachments[1].finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
    attachments[1].flags = 0;
    
    VkAttachmentReference colorReference = {};
    colorReference.attachment = 0;
    colorReference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    VkAttachmentReference depthReference = {};
    depthReference.attachment = 1;
    depthReference.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
    
    VkSubpassDescription subPass = {};
    subPass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subPass.flags = 0;
    subPass.inputAttachmentCount = 0;
    subPass.pInputAttachments = nullptr;
    subPass.colorAttachmentCount = 1;
    subPass.pColorAttachments = &colorReference;
    subPass.pResolveAttachments = nullptr;
    subPass.pDepthStencilAttachment = &depthReference;
    subPass.preserveAttachmentCount = 0;
    subPass.pPreserveAttachments = nullptr;
    
    VkRenderPassCreateInfo renderPassInfo = {};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    renderPassInfo.pNext = nullptr;
    renderPassInfo.attachmentCount = 2;
    renderPassInfo.pAttachments = attachments;
    renderPassInfo.subpassCount = 1;
    renderPassInfo.pSubpasses = &subPass;
    renderPassInfo.dependencyCount = 0;
    renderPassInfo.pDependencies = nullptr;
    if (vkCreateRenderPass(device, &renderPassInfo, nullptr, &renderPass) != VK_SUCCESS) {
        return false;
    }
    
    Log::Print(Log::Level::Debug, nullptr, []{ return "render pass created"; });
    return true;
}

void Context::FreeRenderPass() {
    if (renderPass != VK_NULL_HANDLE) {
        Log::Print(Log::Level::Debug, nullptr, []{ return "freeing render pass"; });
        vkDestroyRenderPass(device, renderPass, nullptr);
        renderPass = VK_NULL_HANDLE;
    }
    if (drawFence != VK_NULL_HANDLE) {
        Log::Print(Log::Level::Debug, nullptr, []{ return "freeing draw fence"; });
        vkDestroyFence(device, drawFence, nullptr);
        drawFence = VK_NULL_HANDLE;
    }
    if (imageAcquiredSemaphore != VK_NULL_HANDLE) {
        Log::Print(Log::Level::Debug, nullptr, []{ return "freeing image acquired semaphore"; });
        vkDestroySemaphore(device, imageAcquiredSemaphore, nullptr);
        imageAcquiredSemaphore = VK_NULL_HANDLE;
    }
}

bool Context::CreateShaders() {
    static const char *vertexShaderText =
        "#version 400\n"
        "#extension GL_ARB_separate_shader_objects : enable\n"
        "#extension GL_ARB_shading_language_420pack : enable\n"
        "layout (push_constant) uniform bufferVals {\n"
        "    mat4 mvp;\n"
        "} myBufferVals;\n"
        "layout (location = 0) in vec4 pos;\n"
        "layout (location = 1) in vec4 inColor;\n"
        "layout (location = 0) out vec4 outColor;\n"
        "void main() {\n"
        "   outColor = inColor;\n"
        "   gl_Position = myBufferVals.mvp * pos;\n"
        "}\n";
    
    std::vector<unsigned int> vertexSpv;
    if (!GLSLtoSPV(VK_SHADER_STAGE_VERTEX_BIT, vertexShaderText, vertexSpv)) {
        return false;
    }
    VkShaderModuleCreateInfo vertexShaderInfo;
    vertexShaderInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    vertexShaderInfo.pNext = nullptr;
    vertexShaderInfo.flags = 0;
    vertexShaderInfo.codeSize = vertexSpv.size() * sizeof(unsigned int);
    vertexShaderInfo.pCode = vertexSpv.data();
    if (vkCreateShaderModule(device, &vertexShaderInfo, nullptr, &vertexShader) != VK_SUCCESS) {
        return false;
    }
  
    static const char *fragmentShaderText =
        "#version 400\n"
        "#extension GL_ARB_separate_shader_objects : enable\n"
        "#extension GL_ARB_shading_language_420pack : enable\n"
        "layout (location = 0) in vec4 color;\n"
        "layout (location = 0) out vec4 outColor;\n"
        "void main() {\n"
        "   outColor = color;\n"
        "}\n";
    std::vector<unsigned int> fragmentSpv;
    if (!GLSLtoSPV(VK_SHADER_STAGE_FRAGMENT_BIT, fragmentShaderText, fragmentSpv)) {
        return false;
    }
    VkShaderModuleCreateInfo fragmentShaderInfo;
    fragmentShaderInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    fragmentShaderInfo.pNext = nullptr;
    fragmentShaderInfo.flags = 0;
    fragmentShaderInfo.codeSize = fragmentSpv.size() * sizeof(unsigned int);
    fragmentShaderInfo.pCode = fragmentSpv.data();
    if (vkCreateShaderModule(device, &fragmentShaderInfo, nullptr, &fragmentShader) != VK_SUCCESS) {
        return false;
    }
    
    Log::Print(Log::Level::Debug, nullptr, []{ return "shaders created"; });
    return true;
}

void Context::FreeShaders() {
   if (fragmentShader != VK_NULL_HANDLE) {
       Log::Print(Log::Level::Debug, nullptr, []{ return "freeing fragment shader"; });
       vkDestroyShaderModule(device, fragmentShader, nullptr);
       fragmentShader = VK_NULL_HANDLE;
   }
   if (vertexShader != VK_NULL_HANDLE) {
       Log::Print(Log::Level::Debug, nullptr, []{ return "freeing vertex shader"; });
       vkDestroyShaderModule(device, vertexShader, nullptr);
       vertexShader = VK_NULL_HANDLE;
   }
}

bool Context::CreateFrameBuffers() {
    frameBuffers.clear();
    for (FrameBufferInfo &info : colorBuffers) {
        VkImageView attachments[2];
        attachments[0] = info.view;
        attachments[1] = depthBuffer.view;
        
        VkFramebufferCreateInfo frameBufferInfo = {};
        frameBufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        frameBufferInfo.pNext = nullptr;
        frameBufferInfo.renderPass = renderPass;
        frameBufferInfo.attachmentCount = 2;
        frameBufferInfo.pAttachments = attachments;
        frameBufferInfo.width = width;
        frameBufferInfo.height = height;
        frameBufferInfo.layers = 1;
        VkFramebuffer frameBuffer;
        if (vkCreateFramebuffer(device, &frameBufferInfo, nullptr, &frameBuffer) != VK_SUCCESS) {
            return false;
        }
        frameBuffers.push_back(frameBuffer);
    }
    
    Log::Print(Log::Level::Debug, nullptr, [&]{ return to_string(frameBuffers.size()) + " frame buffers created"; });
    return true;
}

void Context::FreeFrameBuffers() {
    for (VkFramebuffer &frameBuffer : frameBuffers) {
        Log::Print(Log::Level::Debug, nullptr, []{ return "freeing frame buffer"; });
        vkDestroyFramebuffer(device, frameBuffer, nullptr);
    }
    frameBuffers.clear();
}

bool Context::CreatePipeline() {
    VkDynamicState dynamicStateEnables[VK_DYNAMIC_STATE_RANGE_SIZE];
    memset(dynamicStateEnables, 0, sizeof(dynamicStateEnables));
    VkPipelineDynamicStateCreateInfo dynamicStateInfo = {};
    dynamicStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    dynamicStateInfo.pNext = nullptr;
    dynamicStateInfo.pDynamicStates = dynamicStateEnables;
    dynamicStateInfo.dynamicStateCount = 0;    // Individual dynamic states will be enabled below.
    
    VkPipelineShaderStageCreateInfo shaderStageInfos[2];
    shaderStageInfos[0] = {};
    shaderStageInfos[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    shaderStageInfos[0].pNext = nullptr;
    shaderStageInfos[0].pSpecializationInfo = nullptr;
    shaderStageInfos[0].flags = 0;
    shaderStageInfos[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
    shaderStageInfos[0].pName = "main";
    shaderStageInfos[0].module = vertexShader;
    shaderStageInfos[1] = {};
    shaderStageInfos[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    shaderStageInfos[1].pNext = nullptr;
    shaderStageInfos[1].pSpecializationInfo = nullptr;
    shaderStageInfos[1].flags = 0;
    shaderStageInfos[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    shaderStageInfos[1].pName = "main";
    shaderStageInfos[1].module = fragmentShader;
    
    VkPipelineVertexInputStateCreateInfo vertexInputStateInfo = {};
    // TODO: This currently is set to match SimpleGeometryRenderer.
    VkVertexInputBindingDescription binding = {};
    binding.binding = 0;
    binding.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    binding.stride = 32;
    VkVertexInputAttributeDescription attributes[2];
    attributes[0] = {};
    attributes[0].binding = 0;
    attributes[0].location = 0;
    attributes[0].format = VK_FORMAT_R32G32B32A32_SFLOAT;
    attributes[0].offset = 0;
    attributes[1] = {};
    attributes[1].binding = 0;
    attributes[1].location = 1;
    attributes[1].format = VK_FORMAT_R32G32B32A32_SFLOAT;
    attributes[1].offset = 16;
    vertexInputStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vertexInputStateInfo.pNext = nullptr;
    vertexInputStateInfo.flags = 0;
    vertexInputStateInfo.vertexBindingDescriptionCount = 1;
    vertexInputStateInfo.pVertexBindingDescriptions = &binding;
    vertexInputStateInfo.vertexAttributeDescriptionCount = 2;
    vertexInputStateInfo.pVertexAttributeDescriptions = attributes;
    
    VkPipelineInputAssemblyStateCreateInfo inputAssemblyStateInfo = {};
    inputAssemblyStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    inputAssemblyStateInfo.pNext = nullptr;
    inputAssemblyStateInfo.flags = 0;
    inputAssemblyStateInfo.primitiveRestartEnable = VK_FALSE;
    inputAssemblyStateInfo.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    
    VkPipelineRasterizationStateCreateInfo rasterizationStateInfo = {};
    rasterizationStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rasterizationStateInfo.pNext = nullptr;
    rasterizationStateInfo.flags = 0;
    rasterizationStateInfo.polygonMode = VK_POLYGON_MODE_FILL;
    rasterizationStateInfo.cullMode = VK_CULL_MODE_FRONT_BIT;
    rasterizationStateInfo.frontFace = VK_FRONT_FACE_CLOCKWISE;
    rasterizationStateInfo.depthClampEnable = VK_FALSE;
    rasterizationStateInfo.rasterizerDiscardEnable = VK_FALSE;
    rasterizationStateInfo.depthBiasEnable = VK_FALSE;
    rasterizationStateInfo.depthBiasConstantFactor = 0;
    rasterizationStateInfo.depthBiasClamp = 0;
    rasterizationStateInfo.depthBiasSlopeFactor = 0;
    rasterizationStateInfo.lineWidth = 1.0f;

    VkPipelineColorBlendAttachmentState attachmentState[1];
    attachmentState[0].colorWriteMask = 0xf;
    attachmentState[0].blendEnable = VK_FALSE;
    attachmentState[0].alphaBlendOp = VK_BLEND_OP_ADD;
    attachmentState[0].colorBlendOp = VK_BLEND_OP_ADD;
    attachmentState[0].srcColorBlendFactor = VK_BLEND_FACTOR_ZERO;
    attachmentState[0].dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
    attachmentState[0].srcAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
    attachmentState[0].dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
    VkPipelineColorBlendStateCreateInfo colorBlendStateInfo = {};
    colorBlendStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    colorBlendStateInfo.pNext = nullptr;
    colorBlendStateInfo.flags = 0;
    colorBlendStateInfo.attachmentCount = 1;
    colorBlendStateInfo.pAttachments = attachmentState;
    colorBlendStateInfo.logicOpEnable = VK_FALSE;
    colorBlendStateInfo.logicOp = VK_LOGIC_OP_NO_OP;
    colorBlendStateInfo.blendConstants[0] = 1.0f;
    colorBlendStateInfo.blendConstants[1] = 1.0f;
    colorBlendStateInfo.blendConstants[2] = 1.0f;
    colorBlendStateInfo.blendConstants[3] = 1.0f;
    
    VkPipelineViewportStateCreateInfo viewPortStateInfo = {};
    viewPortStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewPortStateInfo.pNext = nullptr;
    viewPortStateInfo.flags = 0;
    viewPortStateInfo.viewportCount = 1;
    dynamicStateEnables[dynamicStateInfo.dynamicStateCount++] = VK_DYNAMIC_STATE_VIEWPORT;
    viewPortStateInfo.scissorCount = 1;
    dynamicStateEnables[dynamicStateInfo.dynamicStateCount++] = VK_DYNAMIC_STATE_SCISSOR;
    viewPortStateInfo.pScissors = nullptr;
    viewPortStateInfo.pViewports = nullptr;
    
    VkPipelineDepthStencilStateCreateInfo depthStencilStateInfo = {};
    depthStencilStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
    depthStencilStateInfo.pNext = nullptr;
    depthStencilStateInfo.flags = 0;
    depthStencilStateInfo.depthTestEnable = VK_TRUE;
    depthStencilStateInfo.depthWriteEnable = VK_TRUE;
    depthStencilStateInfo.depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL;
    depthStencilStateInfo.depthBoundsTestEnable = VK_FALSE;
    depthStencilStateInfo.minDepthBounds = 0;
    depthStencilStateInfo.maxDepthBounds = 0;
    depthStencilStateInfo.stencilTestEnable = VK_FALSE;
    depthStencilStateInfo.back.failOp = VK_STENCIL_OP_KEEP;
    depthStencilStateInfo.back.passOp = VK_STENCIL_OP_KEEP;
    depthStencilStateInfo.back.compareOp = VK_COMPARE_OP_ALWAYS;
    depthStencilStateInfo.back.compareMask = 0;
    depthStencilStateInfo.back.reference = 0;
    depthStencilStateInfo.back.depthFailOp = VK_STENCIL_OP_KEEP;
    depthStencilStateInfo.back.writeMask = 0;
    depthStencilStateInfo.front = depthStencilStateInfo.back;

    VkPipelineMultisampleStateCreateInfo multiSampleStateInfo = {};
    multiSampleStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multiSampleStateInfo.pNext = nullptr;
    multiSampleStateInfo.flags = 0;
    multiSampleStateInfo.pSampleMask = nullptr;
    multiSampleStateInfo.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
    multiSampleStateInfo.sampleShadingEnable = VK_FALSE;
    multiSampleStateInfo.alphaToCoverageEnable = VK_FALSE;
    multiSampleStateInfo.alphaToOneEnable = VK_FALSE;
    multiSampleStateInfo.minSampleShading = 0.0;

    VkGraphicsPipelineCreateInfo pipelineInfo = {};
    pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pipelineInfo.pNext = nullptr;
    pipelineInfo.layout = pipelineLayout;
    pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;
    pipelineInfo.basePipelineIndex = 0;
    pipelineInfo.flags = 0;
    pipelineInfo.pDynamicState = &dynamicStateInfo;
    pipelineInfo.pStages = shaderStageInfos;
    pipelineInfo.stageCount = 2;
    pipelineInfo.pVertexInputState = &vertexInputStateInfo;
    pipelineInfo.pInputAssemblyState = &inputAssemblyStateInfo;
    pipelineInfo.pRasterizationState = &rasterizationStateInfo;
    pipelineInfo.pColorBlendState = &colorBlendStateInfo;
    pipelineInfo.pTessellationState = nullptr;
    pipelineInfo.pMultisampleState = &multiSampleStateInfo;
    pipelineInfo.pViewportState = &viewPortStateInfo;
    pipelineInfo.pDepthStencilState = &depthStencilStateInfo;
    pipelineInfo.renderPass = renderPass;
    pipelineInfo.subpass = 0;
    if (vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &pipeline) != VK_SUCCESS) {
        return false;
    }

    Log::Print(Log::Level::Debug, nullptr, []{ return "pipeline created"; });
    return true;
}

void Context::FreePipeline() {
    if (pipeline != VK_NULL_HANDLE) {
        Log::Print(Log::Level::Debug, nullptr, []{ return "freeing pipeline"; });
        vkDestroyPipeline(device, pipeline, nullptr);
        pipeline = VK_NULL_HANDLE;
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
    
    Log::Print(Log::Level::Debug, nullptr, []{ return "command buffer pool created"; });
    return true;
}

void Context::FreeCommandBufferPool() {
   if (commandBufferPool != VK_NULL_HANDLE) {
       Log::Print(Log::Level::Debug, nullptr, []{ return "freeing command buffer pool"; });
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

    Log::Print(Log::Level::Debug, nullptr, []{ return "command buffer created"; });
    return true;
}

void Context::FreeCommandBuffer() {
    if (commandBuffer != VK_NULL_HANDLE) {
        Log::Print(Log::Level::Debug, nullptr, []{ return "freeing command buffer"; });
        vkFreeCommandBuffers(device, commandBufferPool, 1, &commandBuffer);
        commandBuffer = VK_NULL_HANDLE;
    }
}

bool Context::GLSLtoSPV(const VkShaderStageFlagBits shaderType, const char *shader, std::vector<unsigned int> &spirv) {
    MVKGLSLConversionShaderStage shaderStage;
    switch (shaderType) {
        case VK_SHADER_STAGE_VERTEX_BIT:
            shaderStage = kMVKGLSLConversionShaderStageVertex;
            break;
        case VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT:
            shaderStage = kMVKGLSLConversionShaderStageTessControl;
            break;
        case VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT:
            shaderStage = kMVKGLSLConversionShaderStageTessEval;
            break;
        case VK_SHADER_STAGE_GEOMETRY_BIT:
            shaderStage = kMVKGLSLConversionShaderStageGeometry;
            break;
        case VK_SHADER_STAGE_FRAGMENT_BIT:
            shaderStage = kMVKGLSLConversionShaderStageFragment;
            break;
        case VK_SHADER_STAGE_COMPUTE_BIT:
            shaderStage = kMVKGLSLConversionShaderStageCompute;
            break;
        default:
            shaderStage = kMVKGLSLConversionShaderStageAuto;
            break;
    }

    mvk::GLSLToSPIRVConverter glslConverter;
    glslConverter.setGLSL(shader);
    bool wasConverted = glslConverter.convert(shaderStage, false, false);
    if (wasConverted) {
        spirv = glslConverter.getSPIRV();
    }
    return wasConverted;
}

}    // Namespace Vulkan.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.
