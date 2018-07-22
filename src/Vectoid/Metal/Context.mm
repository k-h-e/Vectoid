#include <kxm/Vectoid/Metal/Context.h>

namespace kxm {
namespace Vectoid {
namespace Metal {

Context::Context(MTKView *metalView) {
    commandQueue  = nil;
    pipelineState = nil;
    renderEncoder = nil;
    
    id<MTLDevice>   device         = metalView.device;
    id<MTLLibrary>  defaultLibrary = [device newDefaultLibrary];
    id<MTLFunction> vertexShader   = [defaultLibrary newFunctionWithName: @"vertexShader"];
    id<MTLFunction> fragmentShader = [defaultLibrary newFunctionWithName: @"fragmentShader"];
    
    MTLRenderPipelineDescriptor *pipelineStateDescriptor = [[MTLRenderPipelineDescriptor alloc] init];
    pipelineStateDescriptor.label = @"Simple Pipeline";
    pipelineStateDescriptor.vertexFunction = vertexShader;
    pipelineStateDescriptor.fragmentFunction = fragmentShader;
    pipelineStateDescriptor.colorAttachments[0].pixelFormat = metalView.colorPixelFormat;
    NSError *error = nil;
    pipelineState = [device newRenderPipelineStateWithDescriptor: pipelineStateDescriptor error: &error];
    assert (pipelineState != nil);
    
    commandQueue = [device newCommandQueue];
}

}    // Namespace Metal.
}    // Namespace Vectoid.
}    // Namespace kxm.
