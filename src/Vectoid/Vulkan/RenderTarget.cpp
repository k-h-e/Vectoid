#include <kxm/Vectoid/Vulkan/RenderTarget.h>

#include <kxm/Core/logging.h>
#include <kxm/Vectoid/Vulkan/AgeColoredParticles.h>
#include <kxm/Vectoid/Vulkan/Camera.h>
#include <kxm/Vectoid/Vulkan/Context.h>
#include <kxm/Vectoid/Vulkan/CoordSys.h>
#include <kxm/Vectoid/Vulkan/Geode.h>
#include <kxm/Vectoid/Vulkan/Glyphs.h>
#include <kxm/Vectoid/Vulkan/ParticlesRenderer.h>
#include <kxm/Vectoid/Vulkan/PerspectiveProjection.h>
#include <kxm/Vectoid/Vulkan/TestTriangle.h>
#include <kxm/Vectoid/Vulkan/TextConsole.h>

using namespace std;

namespace kxm {
namespace Vectoid {
namespace Vulkan {

RenderTarget::RenderTarget(void *view) {
    Core::Log().Stream() << "Vulkan render target" << endl;
    
    context_ = make_shared<Context>(view);
}

void RenderTarget::SetSceneGraph(const std::shared_ptr<SceneGraphNode> &sceneGraphRoot) {
    sceneGraphRoot_ = sceneGraphRoot;
}

void RenderTarget::RenderFrame() {
    Core::Log().Stream() << "RenderFrame()" << endl;

    if (!context_->Operative() || !sceneGraphRoot_) {
        return;
    }
    
    VkResult acquireResult = vkAcquireNextImageKHR(
        context_->device, context_->swapChain, UINT64_MAX, context_->imageAcquiredSemaphore, VK_NULL_HANDLE,
        &context_->currentBuffer);
    if (acquireResult == VK_SUBOPTIMAL_KHR) {
        Core::Log().Stream() << "image suboptimal" << endl;
    }
    else if (acquireResult == VK_ERROR_OUT_OF_DATE_KHR) {
        Core::Log().Stream() << "image out of date" << endl;
        context_->RecoverFromOutOfDateImage();
    }
    else if (acquireResult == VK_SUCCESS) {
        Core::Log().Stream() << "image acquired" << endl;
        if (context_->CreateCommandBuffer()) {
            VkCommandBufferBeginInfo bufferBeginInfo = {};
            bufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
            bufferBeginInfo.pNext = nullptr;
            bufferBeginInfo.flags = 0;
            bufferBeginInfo.pInheritanceInfo = nullptr;
            if (vkBeginCommandBuffer(context_->commandBuffer, &bufferBeginInfo) == VK_SUCCESS) {
                VkClearValue clearValues[2];
                clearValues[0] = {};
                clearValues[0].color.float32[0] = 0.2f;
                clearValues[0].color.float32[1] = 0.2f;
                clearValues[0].color.float32[2] = 0.2f;
                clearValues[0].color.float32[3] = 0.2f;
                clearValues[1] = {};
                clearValues[1].depthStencil.depth = 1.0f;
                clearValues[1].depthStencil.stencil = 0;
                
                VkRenderPassBeginInfo passBeginInfo;
                passBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
                passBeginInfo.pNext = nullptr;
                passBeginInfo.renderPass = context_->renderPass;
                passBeginInfo.framebuffer = context_->frameBuffers[context_->currentBuffer];
                passBeginInfo.renderArea.offset.x = 0;
                passBeginInfo.renderArea.offset.y = 0;
                passBeginInfo.renderArea.extent.width = context_->width;
                passBeginInfo.renderArea.extent.height = context_->height;
                passBeginInfo.clearValueCount = 2;
                passBeginInfo.pClearValues = clearValues;
                vkCmdBeginRenderPass(context_->commandBuffer, &passBeginInfo, VK_SUBPASS_CONTENTS_INLINE);
                
                vkCmdBindPipeline(context_->commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, context_->pipeline);
                
                VkViewport viewPort = {};
                viewPort.height = (float)context_->height;
                viewPort.width = (float)context_->width;
                viewPort.minDepth = 0.0f;
                viewPort.maxDepth = 1.0f;
                viewPort.x = 0;
                viewPort.y = 0;
                vkCmdSetViewport(context_->commandBuffer, 0, 1, &viewPort);

                VkRect2D scissors = {};
                scissors.extent.width = context_->width;
                scissors.extent.height = context_->height;
                scissors.offset.x = 0;
                scissors.offset.y = 0;
                vkCmdSetScissor(context_->commandBuffer, 0, 1, &scissors);
                
                // Re-init object transform as Vulkan clipping transform...
                // Note that Vulkan clip space has inverted y and half z.
                FullTransform clippingTransform;    // Identity.
                clippingTransform.Element(1, 1) = -1.0f;
                clippingTransform.Element(2, 2) =   .5f;
                clippingTransform.Element(3, 2) =   .5f;
                context_->UpdateObjectTransform(clippingTransform);
                context_->ApplyObjectTransform();
                
                sceneGraphRoot_->Render();
                
                vkCmdEndRenderPass(context_->commandBuffer);
                
                if (vkEndCommandBuffer(context_->commandBuffer) == VK_SUCCESS) {
                    VkPipelineStageFlags flags = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
                    VkSubmitInfo submitInfo = {};
                    submitInfo.pNext = nullptr;
                    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
                    submitInfo.waitSemaphoreCount = 1;
                    submitInfo.pWaitSemaphores = &context_->imageAcquiredSemaphore;
                    submitInfo.pWaitDstStageMask = &flags;
                    submitInfo.commandBufferCount = 1;
                    submitInfo.pCommandBuffers = &context_->commandBuffer;
                    submitInfo.signalSemaphoreCount = 0;
                    submitInfo.pSignalSemaphores = nullptr;
                    if (vkQueueSubmit(context_->graphicsQueue, 1, &submitInfo, context_->drawFence) == VK_SUCCESS) {
                        VkResult fenceResult;
                        do {
                            fenceResult = vkWaitForFences(context_->device, 1, &context_->drawFence, VK_TRUE,
                                                          100000000);
                        } while (fenceResult == VK_TIMEOUT);
                        if (fenceResult == VK_SUCCESS) {
                            VkPresentInfoKHR presentInfo = {};
                            presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
                            presentInfo.pNext = nullptr;
                            presentInfo.swapchainCount = 1;
                            presentInfo.pSwapchains = &context_->swapChain;
                            presentInfo.pImageIndices = &context_->currentBuffer;
                            presentInfo.pWaitSemaphores = nullptr;
                            presentInfo.waitSemaphoreCount = 0;
                            presentInfo.pResults = nullptr;
                            if (vkQueuePresentKHR(context_->presentQueue, &presentInfo) == VK_SUCCESS) {
                                Core::Log().Stream() << "frame presented" << endl;
                            }
                        }
                    }
                }
            }
        }
        context_->FreeCommandBuffer();
    }
}

shared_ptr<Vectoid::AgeColoredParticles> RenderTarget::NewAgeColoredParticles(const shared_ptr<Particles> &particles) {
    return shared_ptr<AgeColoredParticles>(new AgeColoredParticles(context_, particles));
}

shared_ptr<Vectoid::Camera> RenderTarget::NewCamera() {
    return shared_ptr<Camera>(new Camera(context_));
}

shared_ptr<Vectoid::CoordSys> RenderTarget::NewCoordSys() {
    return shared_ptr<CoordSys>(new CoordSys(context_));
}

shared_ptr<Vectoid::Geode> RenderTarget::NewGeode(const std::shared_ptr<GeometryInterface> &geometry) {
    return shared_ptr<Geode>(new Geode(geometry));
}

shared_ptr<Vectoid::Glyphs> RenderTarget::NewGlyphs() {
    return shared_ptr<Glyphs>(new Glyphs(context_));
}

shared_ptr<Vectoid::ParticlesRenderer> RenderTarget::NewParticlesRenderer(const shared_ptr<Particles> &particles) {
    return shared_ptr<ParticlesRenderer>(new ParticlesRenderer(context_, particles));
}

shared_ptr<Vectoid::PerspectiveProjection> RenderTarget::NewPerspectiveProjection() {
    return shared_ptr<PerspectiveProjection>(new PerspectiveProjection(context_));
}

shared_ptr<Vectoid::TestTriangle> RenderTarget::NewTestTriangle() {
    return shared_ptr<TestTriangle>(new TestTriangle(context_));
}

shared_ptr<Vectoid::TextConsole> RenderTarget::NewTextConsole(
        int width, int height, float glyphWidth, float glyphHeight, const shared_ptr<Vectoid::Glyphs> &glyphs) {
    return shared_ptr<TextConsole>(new TextConsole(context_, width, height, glyphWidth, glyphHeight, glyphs));
}

}    // Namespace Vulkan.
}    // Namespace Vectoid.
}    // Namespace kxm.

