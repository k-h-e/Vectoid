#import "MetalVideoView.h"

#include <memory>
#include <kxm/Zarch/Zarch.h>
#include <kxm/Zarch/ControlsState.h>
#include <kxm/Zarch/Video/Metal/RenderTarget.h>

using namespace std;
using namespace kxm::Zarch;

@interface MetalVideoView () {
    shared_ptr<Zarch>         _zarch;
    shared_ptr<ControlsState> _controlsState;
    CGSize                    _size;
}
@end

@implementation MetalVideoView

- (void)awakeFromNib {
    [super awakeFromNib];

    self.device = MTLCreateSystemDefaultDevice();
    assert(self.device != nil);

    self.paused                = YES;
    self.enableSetNeedsDisplay = YES;
    
}

- (std::shared_ptr<kxm::Zarch::Video::RenderTargetInterface>)getRenderTarget {
    return make_shared<Video::Metal::RenderTarget>(self);
}

- (void)setZarch: (const std::shared_ptr<kxm::Zarch::Zarch> &)aZarch
        controlsState: (const std::shared_ptr<kxm::Zarch::ControlsState> &)aControlsState {
    _zarch         = aZarch;
    _controlsState = aControlsState;
    _size.width  = 0.0f;
    _size.height = 0.0f;
}

- (void)drawRect: (NSRect)bounds {
    if (_zarch) {
        CGSize newSize = bounds.size;    // TODO: Better use self.frame.size?
        if ((newSize.width != _size.width) || (newSize.height != _size.height)) {
            _size.width  = newSize.width;
            _size.height = newSize.height;
            _zarch->SetViewPort((int)(_size.width +.5f), (int)(_size.height + .5f));
        }
        
        _zarch->PrepareFrame(*_controlsState);
        _zarch->RenderFrame();
    }
}

- (BOOL)acceptsFirstResponder {
    return YES;
}

@end
