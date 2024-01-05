///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/SceneGraph/Vulkan/RenderTarget.h>

#include <K/Core/Log.h>
#include <Vectoid/SceneGraph/RenderVisitor.h>
#include <Vectoid/SceneGraph/Vulkan/AgeColoredParticles.h>
#include <Vectoid/SceneGraph/Vulkan/Camera.h>
#include <Vectoid/SceneGraph/Vulkan/Context.h>
#include <Vectoid/SceneGraph/Vulkan/CoordSys.h>
#include <Vectoid/SceneGraph/Vulkan/Geode.h>
#include <Vectoid/SceneGraph/Vulkan/LineSegments.h>
#include <Vectoid/SceneGraph/Vulkan/LitTriangles.h>
#include <Vectoid/SceneGraph/Vulkan/Glyphs.h>
#include <Vectoid/SceneGraph/Vulkan/ParticlesRenderer.h>
#include <Vectoid/SceneGraph/Vulkan/PerspectiveProjection.h>
#include <Vectoid/SceneGraph/Vulkan/SimpleGeometryRenderer.h>
#include <Vectoid/SceneGraph/Vulkan/SimpleLighting.h>
#include <Vectoid/SceneGraph/Vulkan/TerrainRenderer.h>
#include <Vectoid/SceneGraph/Vulkan/TestTriangle.h>
#include <Vectoid/SceneGraph/Vulkan/TextConsole.h>

using namespace std;
using K::Core::Log;
using Vectoid::Core::LineSegmentProviderInterface;
using Vectoid::Core::Particles;
using Vectoid::Core::TriangleProviderInterface;

namespace Vectoid {
namespace SceneGraph {
namespace Vulkan {

RenderTarget::RenderTarget(void *view) {
    Log::Print(Log::Level::Debug, this, []{ return "Vulkan render target"; });
    
    context_ = make_shared<Context>(view);
}

void RenderTarget::SetSceneGraph(const std::shared_ptr<Node> &sceneGraphRoot) {
    sceneGraphRoot_ = sceneGraphRoot;
}

void RenderTarget::RenderFrame() {
    Log::Print(Log::Level::Debug, this, []{ return "RenderFrame()"; });

    if (!context_->Operative() || !sceneGraphRoot_) {
        return;
    }
    
    VkResult acquireResult = vkAcquireNextImageKHR(
        context_->device, context_->swapChain, UINT64_MAX, context_->imageAcquiredSemaphore, VK_NULL_HANDLE,
        &context_->currentBuffer);
    if (acquireResult == VK_SUBOPTIMAL_KHR) {
        Log::Print(Log::Level::Debug, this, []{ return "image suboptimal"; });
    }
    else if (acquireResult == VK_ERROR_OUT_OF_DATE_KHR) {
        Log::Print(Log::Level::Debug, this, []{ return "image out of date"; });
        context_->RecoverFromOutOfDateImage();
    }
    else if (acquireResult == VK_SUCCESS) {
        Log::Print(Log::Level::Debug, this, []{ return "image acquired"; });
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
                Core::FullTransform clippingTransform;    // Identity.
                clippingTransform.Element(1, 1) = -1.0f;
                clippingTransform.Element(2, 2) =   .5f;
                //clippingTransform.Element(3, 2) =   .5f;
                context_->UpdateObjectTransform(clippingTransform);
                context_->ApplyObjectTransform();
                
                RenderVisitor renderVisitor;
                Visit(sceneGraphRoot_, &renderVisitor, false);
                
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
                                Log::Print(Log::Level::Debug, this, []{ return "frame presented"; });
                            }
                        }
                    }
                }
            }
        }
        context_->FreeCommandBuffer();
    }
}

shared_ptr<::Vectoid::SceneGraph::AgeColoredParticles> RenderTarget::NewAgeColoredParticles(
        const shared_ptr<Core::Particles> &particles) {
    return shared_ptr<Vulkan::AgeColoredParticles>(new AgeColoredParticles(context_, particles));
}

shared_ptr<::Vectoid::SceneGraph::Camera> RenderTarget::NewCamera() {
    return shared_ptr<Vulkan::Camera>(new Camera(context_));
}

shared_ptr<::Vectoid::SceneGraph::CoordSys> RenderTarget::NewCoordSys() {
    return shared_ptr<Vulkan::CoordSys>(new CoordSys(context_));
}

shared_ptr<::Vectoid::SceneGraph::Geode> RenderTarget::NewGeode(const std::shared_ptr<GeometryInterface> &geometry) {
    return shared_ptr<Vulkan::Geode>(new Geode(geometry));
}

shared_ptr<::Vectoid::SceneGraph::Glyphs> RenderTarget::NewGlyphs() {
    return shared_ptr<Vulkan::Glyphs>(new Glyphs(context_));
}

shared_ptr<::Vectoid::SceneGraph::LineSegments> RenderTarget::NewLineSegments(
        const shared_ptr<LineSegmentProviderInterface> &lineSegmentProvider) {
    return make_shared<Vulkan::LineSegments>(lineSegmentProvider);
}

shared_ptr<::Vectoid::SceneGraph::LitTriangles> RenderTarget::NewLitTriangles(
        const shared_ptr<TriangleProviderInterface> &triangleProvider) {
    return make_shared<Vulkan::LitTriangles>(triangleProvider);
}

shared_ptr<::Vectoid::SceneGraph::ParticlesRenderer> RenderTarget::NewParticlesRenderer(
        const shared_ptr<Core::Particles> &particles) {
    return shared_ptr<Vulkan::ParticlesRenderer>(new ParticlesRenderer(context_, particles));
}

shared_ptr<::Vectoid::SceneGraph::PerspectiveProjection> RenderTarget::NewPerspectiveProjection() {
    return shared_ptr<Vulkan::PerspectiveProjection>(new PerspectiveProjection(context_));
}

shared_ptr<::Vectoid::SceneGraph::SimpleGeometryRenderer> RenderTarget::NewSimpleGeometryRenderer(
        const shared_ptr<::Vectoid::SceneGraph::SimpleGeometry> &geometry) {
    return shared_ptr<Vulkan::SimpleGeometryRenderer>(new SimpleGeometryRenderer(context_, geometry));
}

shared_ptr<::Vectoid::SceneGraph::SimpleLighting> RenderTarget::NewSimpleLighting() {
    return make_shared<Vulkan::SimpleLighting>();
}

shared_ptr<::Vectoid::SceneGraph::TerrainRenderer> RenderTarget::NewTerrainRenderer(
        const shared_ptr<::Vectoid::SceneGraph::Terrain> &terrain,
        const shared_ptr<::Vectoid::SceneGraph::MapParameters> &mapParameters) {
    return shared_ptr<Vulkan::TerrainRenderer>(new TerrainRenderer(context_, terrain, mapParameters));
}

shared_ptr<::Vectoid::SceneGraph::TestTriangle> RenderTarget::NewTestTriangle() {
    return shared_ptr<Vulkan::TestTriangle>(new TestTriangle(context_));
}

shared_ptr<::Vectoid::SceneGraph::TextConsole> RenderTarget::NewTextConsole(
        int width, int height, float glyphWidth, float glyphHeight,
        const shared_ptr<Vectoid::SceneGraph::Glyphs> &glyphs) {
    return shared_ptr<Vulkan::TextConsole>(new TextConsole(context_, width, height, glyphWidth, glyphHeight, glyphs));
}

}    // Namespace Vulkan.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.


