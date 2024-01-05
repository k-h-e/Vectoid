///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_SCENEGRAPH_VULKAN_CONTEXT_H_
#define VECTOID_SCENEGRAPH_VULKAN_CONTEXT_H_

#include <vector>
#include <vulkan/vulkan.h>
#include <Vectoid/Core/Transform.h>
#include <Vectoid/Core/FullTransform.h>
#include <Vectoid/SceneGraph/Vulkan/FrameBufferInfo.h>

namespace Vectoid {
namespace SceneGraph {
namespace Vulkan {

//! Holds <c>Vulkan</c>-specific context for scene graph nodes.
/*!
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
    //! Creates the command buffer.
    /*!
     *  \return <c>true</c> in case of success.
     */
    bool CreateCommandBuffer();
    //! Frees the command buffer if it is present.
    void FreeCommandBuffer();
    //! Recovers from out-of-date image condition.
    void RecoverFromOutOfDateImage();
    
    void UpdateObjectTransform(const Core::FullTransform &transform);
    void ApplyObjectTransform();
    const Core::FullTransform &ObjectTransform();
    
    bool GetMemoryIndex(uint32_t typeBits, VkFlags requirementsMask, uint32_t *typeIndex);
    
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
    
    VkPipelineLayout                  pipelineLayout;
    
    VkSemaphore                       imageAcquiredSemaphore;
    VkFence                           drawFence;
    
    VkRenderPass                      renderPass;
    VkShaderModule                    vertexShader;
    VkShaderModule                    fragmentShader;
    std::vector<VkFramebuffer>        frameBuffers;
    
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
    bool CreateLayouts();
    // Frees the layouts if they are present.
    void FreeLayouts();
    bool CreateRenderPass();
    // Frees the render pass if it is present.
    void FreeRenderPass();
    bool CreateShaders();
    // Frees the shaders if they are present.
    void FreeShaders();
    bool CreateFrameBuffers();
    // Frees the frame buffers if they are present.
    void FreeFrameBuffers();
    bool CreatePipeline();
    // Frees the pipeline if it is present.
    void FreePipeline();
    bool CreateCommandBufferPool();
    // Frees the command buffer pool if it is present.
    void FreeCommandBufferPool();
    
    static bool GLSLtoSPV(const VkShaderStageFlagBits shaderType, const char *shader, std::vector<unsigned int> &spirv);
    
    bool                operative_;
    Core::FullTransform currentObjectTransform_;
    bool                currentObjectTransformChanged_;
};

}    // Namespace Vulkan.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_VULKAN_CONTEXT_H_
