#include <kxm/Zarch/Presentation.h>

#include <kxm/Core/logging.h>
#include <kxm/Game/EventLoop.h>
#include <kxm/Zarch/Zarch.h>

using namespace std;
using namespace kxm::Core;
using namespace kxm::Game;

namespace kxm {
namespace Zarch {

Presentation::Presentation(const shared_ptr<EventLoopHub> &eventLoopHub)
        : eventLoop_(new EventLoop<ZarchEvent, EventHandlerCore>(eventLoopHub)),
          lastTrigger_(TriggerEvent::NoTrigger) {
    Zarch::RegisterEvents(eventLoop_.get());
    video_ = shared_ptr<Video::Video>(new Video::Video(eventLoop_));
    
    eventLoop_->RegisterHandler(TriggerEvent::type, this);
}

Presentation::~Presentation() {
    eventLoop_->UnregisterHandlers();
}

void Presentation::PrepareFrame(const ControlsState &controlsState) {
    video_->PrepareFrame(controlsState);
}

void Presentation::SetViewPort(int width, int height) {
    video_->SetViewPort(width, height);
}

void Presentation::RenderFrame() {
    lastTrigger_ = TriggerEvent::NoTrigger;
    while (lastTrigger_ != TriggerEvent::FrameRenderedTrigger) {
        eventLoop_->RunUntilEventOfType(&triggerEvent_.Type());
    }
}

void Presentation::Handle(const TriggerEvent &event) {
    lastTrigger_ = event.trigger;
}

}
}

