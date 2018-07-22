#ifndef KXM_VECTOID_METAL_CONTEXT_H_
#define KXM_VECTOID_METAL_CONTEXT_H_

#import <MetalKit/MetalKit.h>

namespace kxm {
namespace Vectoid {
namespace Metal {

//! Holds <c>Metal</c>-specific context for scene graph nodes.
/*!
 *  \ingroup VectoidMetal
 */
struct Context {
    Context(MTKView *metalView);
    Context(const Context &other) = delete;
    Context &operator=(const Context &other) = delete;
    
    id<MTLCommandQueue>         commandQueue;
    id<MTLRenderPipelineState>  pipelineState;
    id<MTLRenderCommandEncoder> renderEncoder;
};

}    // Namespace Metal.
}    // Namespace Vectoid.
}    // Namespace kxm.

#endif    // KXM_VECTOID_METAL_CONTEXT_H_
