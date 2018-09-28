#include <kxm/Vectoid/Metal/RenderTarget.h>

#include <kxm/Vectoid/Geode.h>
#include <kxm/Vectoid/Metal/AgeColoredParticles.h>
#include <kxm/Vectoid/Metal/Camera.h>
#include <kxm/Vectoid/Metal/Context.h>
#include <kxm/Vectoid/Metal/CoordSys.h>
#include <kxm/Vectoid/Metal/Glyphs.h>
#include <kxm/Vectoid/Metal/ParticlesRenderer.h>
#include <kxm/Vectoid/Metal/PerspectiveProjection.h>
#include <kxm/Vectoid/Metal/TestTriangle.h>
#include <kxm/Vectoid/Metal/TextConsole.h>
#import "ShaderTypes.h"

using namespace std;

namespace kxm {
namespace Vectoid {
namespace Metal {

RenderTarget::RenderTarget(MTKView *metalView) {
    context_   = make_shared<Context>(metalView);
    metalView_ = metalView;
}

void RenderTarget::SetSceneGraph(const std::shared_ptr<SceneGraphNode> &sceneGraphRoot) {
    sceneGraphRoot_ = sceneGraphRoot;
}

void RenderTarget::RenderFrame() {

    // TESTING...
    static const AAPLVertex triangleVertices[] =
    {
        // 2D positions,    RGBA colors
        { {  250,  -250 }, { 1, 0, 0, 1 } },
        { { -250,  -250 }, { 0, 1, 0, 1 } },
        { {    0,   250 }, { 0, 0, 1, 1 } },
    };
    static const vector_uint2 viewportSize = { 2000u, 1000u };

    id<MTLCommandBuffer> commandBuffer = [context_->commandQueue commandBuffer];
    commandBuffer.label = @"Frame Command Buffer";

    MTLRenderPassDescriptor *renderPassDescriptor = metalView_.currentRenderPassDescriptor;
    if(renderPassDescriptor != nil) {
        context_->renderEncoder = [commandBuffer renderCommandEncoderWithDescriptor: renderPassDescriptor];
        context_->renderEncoder.label = @"Frame Render Encoder";

        // TESTING...
        [context_->renderEncoder
         setViewport: (MTLViewport){0.0, 0.0, (double)viewportSize.x, (double)viewportSize.y, -1.0, 1.0 }];
        
        [context_->renderEncoder setRenderPipelineState: context_->pipelineState];

        // TESTING...
        [context_->renderEncoder setVertexBytes: triangleVertices length: sizeof(triangleVertices)
                                 atIndex: AAPLVertexInputIndexVertices];
        [context_->renderEncoder setVertexBytes: &viewportSize length: sizeof(viewportSize)
                                 atIndex: AAPLVertexInputIndexViewportSize];
        [context_->renderEncoder drawPrimitives: MTLPrimitiveTypeTriangle vertexStart: 0 vertexCount: 3];

        if (sceneGraphRoot_) {
            sceneGraphRoot_->Render();
        }
        
        [context_->renderEncoder endEncoding];
        [commandBuffer presentDrawable: metalView_.currentDrawable];
    }
    
    [commandBuffer commit];
}

shared_ptr<Vectoid::AgeColoredParticles> RenderTarget::NewAgeColoredParticles(const shared_ptr<Particles> &particles) {
    return make_shared<AgeColoredParticles>(context_, particles);
}

shared_ptr<Vectoid::Camera> RenderTarget::NewCamera() {
    return make_shared<Camera>(context_);
}

shared_ptr<Vectoid::CoordSys> RenderTarget::NewCoordSys() {
    return make_shared<CoordSys>(context_);
}

shared_ptr<Vectoid::Geode> RenderTarget::NewGeode(const std::shared_ptr<GeometryInterface> &geometry) {
    return make_shared<Geode>(geometry);
}

shared_ptr<Vectoid::Glyphs> RenderTarget::NewGlyphs() {
    return make_shared<Glyphs>(context_);
}

shared_ptr<Vectoid::ParticlesRenderer> RenderTarget::NewParticlesRenderer(const shared_ptr<Particles> &particles) {
    return make_shared<ParticlesRenderer>(context_, particles);
}

shared_ptr<Vectoid::PerspectiveProjection> RenderTarget::NewPerspectiveProjection() {
    return make_shared<PerspectiveProjection>(context_);
}

shared_ptr<Vectoid::TestTriangle> RenderTarget::NewTestTriangle() {
    return make_shared<TestTriangle>(context_);
}

shared_ptr<Vectoid::TextConsole> RenderTarget::NewTextConsole(
        int width, int height, float glyphWidth, float glyphHeight, const shared_ptr<Vectoid::Glyphs> &glyphs) {
    return make_shared<TextConsole>(context_, width, height, glyphWidth, glyphHeight, glyphs);
}

}    // Namespace Metal.
}    // Namespace Vectoid.
}    // Namespace kxm.

