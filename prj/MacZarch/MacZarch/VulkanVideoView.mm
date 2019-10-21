#import "VulkanVideoView.h"

#include <memory>
#import <MetalKit/MetalKit.h>
#include <kxm/Core/logging.h>
#include <kxm/Zarch/Zarch.h>
#include <kxm/Zarch/ControlsState.h>
#include <kxm/Zarch/Video/Vulkan/RenderTarget.h>

using namespace std;
using namespace kxm::Zarch;

@interface VulkanVideoView () {
    shared_ptr<Zarch>         _zarch;
    shared_ptr<ControlsState> _controlsState;
    CGSize                    _size;
}
@end

@implementation VulkanVideoView

- (std::shared_ptr<kxm::Zarch::Video::RenderTargetInterface>)getRenderTarget {
    return make_shared<Video::Vulkan::RenderTarget>((__bridge void *)self);
}

- (void)setZarch: (const std::shared_ptr<kxm::Zarch::Zarch> &)aZarch
        controlsState: (const std::shared_ptr<kxm::Zarch::ControlsState> &)aControlsState {
    _zarch         = aZarch;
    _controlsState = aControlsState;
    _size.width  = 0.0f;
    _size.height = 0.0f;
}

- (void)triggerFrame {
    if (_zarch) {
        CGSize newSize = self.bounds.size;    // TODO: Better use self.frame.size?
        if ((newSize.width != _size.width) || (newSize.height != _size.height)) {
            _size.width  = newSize.width;
            _size.height = newSize.height;
            _zarch->SetViewPort((int)(_size.width +.5f), (int)(_size.height + .5f));
        }
        
        _zarch->PrepareFrame(*_controlsState);
        _zarch->RenderFrame();
    }
}

// Indicates that the view wants to draw using the backing layer instead of using drawRect:.
- (BOOL)wantsUpdateLayer {
    return YES;
}

// Returns a Metal-compatible layer.
+ (Class)layerClass {
    return [CAMetalLayer class];
}

// If the wantsLayer property is set to YES, this method will be invoked to return a layer instance.
- (CALayer *)makeBackingLayer {
    CALayer *layer = [self.class.layerClass layer];
    CGSize viewScale = [self convertSizeToBacking: CGSizeMake(1.0, 1.0)];
    layer.contentsScale = MIN(viewScale.width, viewScale.height);
    return layer;
}

@end
