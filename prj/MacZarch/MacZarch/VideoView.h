#include <memory>

namespace kxm {
namespace Zarch {

class Zarch;
class ControlsState;

namespace Video {

class RenderTargetInterface;

}

}
}

@protocol VideoView

- (std::shared_ptr<kxm::Zarch::Video::RenderTargetInterface>)getRenderTarget;
- (void)setZarch: (const std::shared_ptr<kxm::Zarch::Zarch> &)aZarch
        controlsState: (const std::shared_ptr<kxm::Zarch::ControlsState> &)aControlsState;
- (void)triggerFrame;

@end
