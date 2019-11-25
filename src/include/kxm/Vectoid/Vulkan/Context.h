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
        // Default copy okay.
    };
    struct BufferInfo {
        VkBuffer               buffer;
        VkDeviceMemory         memory;
        VkDescriptorBufferInfo info;
        
        BufferInfo() : buffer(VK_NULL_HANDLE), memory(VK_NULL_HANDLE) {
            info.buffer = VK_NULL_HANDLE;
            info.offset = 0u;
            info.range  = 0u;
        }
        // Default copy okay.
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
    //! Recovers from out-of-date image condition.
    void RecoverFromOutOfDateImage();
    
    VkInstance                        instance;
    VkSurfaceKHR                      surface;
    VkDevice                          device;
    VkPhysicalDevice                  physicalDevice;                    // Valid <=> device present.
    VkPhysicalDeviceMemoryProperties  physicalDeviceMemoryProperties;    // Valid <=> device present.
    uint32_t                          queueFamilyCount;                  // Valid <=> device present.
    uint32_t                          graphicsQueueFamilyIndex;          // Valid <=> device present.
    uint32_t                          presentQueueFamilyIndex;           // Valid <=> device present.
    VkQueue                           graphicsQueue;                     // Valid <=> device present.
    VkQueue                           presentQueue;                      // Valid <=> device present.
    VkSwapchainKHR                    swapChain;
    uint32_t                          width;                             // Valid <=> swap chain present.
    uint32_t                          height;                            // Valid <=> swap chain present.
    std::vector<FrameBufferInfo>      colorBuffers;
    VkFormat                          colorFormat;                       // Valid <=> swap chain present.
    uint32_t                          currentBuffer;
    FrameBufferInfo                   depthBuffer;
    VkFormat                          depthFormat;                       // Valid <=> depth buffer present.
    BufferInfo                        uniformBuffer;
    VkDescriptorSetLayout             descriptorSetLayout;
    VkPipelineLayout                  pipelineLayout;
    VkDescriptorPool                  descriptorPool;
    VkDescriptorSet                   descriptorSet;
    VkSemaphore                       imageAcquiredSemaphore;
    VkFence                           drawFence;
    VkRenderPass                      renderPass;
    VkShaderModule                    vertexShader;
    VkShaderModule                    fragmentShader;
    std::vector<VkFramebuffer>        frameBuffers;
    BufferInfo                        vertexBuffer;
    VkVertexInputBindingDescription   vertexInputBinding;                // Valid <=> vertex buffer present.
    VkVertexInputAttributeDescription vertexInputAttributes[2];          // Valid <=> vertex buffer present.
    VkPipeline                        pipeline;
    VkCommandPool                     commandBufferPool;
    VkCommandBuffer                   commandBuffer;
    
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
    bool CreateLayouts();
    // Frees the layouts if they are present.
    void FreeLayouts();
    bool CreateDescriptorSets();
    // Frees the descriptor sets if they are present.
    void FreeDescriptorSets();
    bool CreateRenderPass();
    // Frees the render pass if it is present.
    void FreeRenderPass();
    bool CreateShaders();
    // Frees the shaders if they are present.
    void FreeShaders();
    bool CreateFrameBuffers();
    // Frees the frame buffers if they are present.
    void FreeFrameBuffers();
    bool CreateVertexBuffer();
    // Frees the vertex buffer if it is present.
    void FreeVertexBuffer();
    bool CreatePipeline();
    // Frees the pipeline if it is present.
    void FreePipeline();
    bool CreateCommandBufferPool();
    // Frees the command buffer pool if it is present.
    void FreeCommandBufferPool();
    
    bool getMemoryIndex(uint32_t typeBits, VkFlags requirementsMask, uint32_t *typeIndex);
    static bool GLSLtoSPV(const VkShaderStageFlagBits shaderType, const char *shader, std::vector<unsigned int> &spirv);
    
    bool operative_;
};

}    // Namespace Vulkan.
}    // Namespace Vectoid.
}    // Namespace kxm.

#endif    // KXM_VECTOID_VULKAN_CONTEXT_H_
