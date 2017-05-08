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

- (void)awakeFromNib;

- (void)setZarch: (const std::shared_ptr<kxm::Zarch::Zarch> &)aZarch
        controlsState: (const std::shared_ptr<kxm::Zarch::ControlsState> &)aControlsState;

- (void)prepareOpenGL;
- (void)drawRect: (NSRect)bounds;

@end
