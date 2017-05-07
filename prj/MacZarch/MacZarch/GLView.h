#import <Cocoa/Cocoa.h>

#include <memory>

namespace kxm {
namespace Zarch {
    class Zarch;
    class ControlsState;
}
}

@interface GLView : NSOpenGLView {
}

- (void)setZarch: (const std::shared_ptr<kxm::Zarch::Zarch> &)aZarch
        controlsState: (const std::shared_ptr<kxm::Zarch::ControlsState> &)aControlsState;
- (void)drawRect: (NSRect)bounds;

@end
