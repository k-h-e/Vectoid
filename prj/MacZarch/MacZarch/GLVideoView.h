#include <memory>
#import <Cocoa/Cocoa.h>
#import "VideoView.h"

namespace kxm {
namespace Zarch {
    class Zarch;
    class ControlsState;
}
}

@interface GLVideoView : NSOpenGLView <VideoView> {
}

- (void)awakeFromNib;
- (void)prepareOpenGL;
- (void)drawRect: (NSRect)bounds;

@end
