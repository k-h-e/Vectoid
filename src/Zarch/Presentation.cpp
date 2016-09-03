#include <Zarch/Presentation.h>

#include <kxm/Core/logging.h>
#include <Game/EventLoop.h>
#include <Zarch/ControlsState.h>
#include <Zarch/Zarch.h>
#include <Zarch/Events/FrameTimeEvent.h>
#include <Zarch/Events/LanderMoveEvent.h>
#include <Zarch/Events/LanderVelocityEvent.h>
#include <Zarch/Events/LanderThrusterEvent.h>
#include <Zarch/Events/ControlsStateEvent.h>

using namespace std;
using namespace kxm::Core;
using namespace kxm::Game;

namespace kxm {
namespace Zarch {

Presentation::Presentation(const shared_ptr<EventLoopHub> &eventLoopHub)
        : eventLoop_(new EventLoop<ZarchEvent, EventHandlerCore>(eventLoopHub)) {
    Zarch::RegisterEvents(eventLoop_.get());
    video_ = shared_ptr<Video::Video>(new Video::Video(eventLoop_));
}

Presentation::~Presentation() {
    eventLoop_->UnregisterHandlers();
}

void Presentation::PrepareFrame(const ControlsState &controlsState) {
    eventLoop_->Post(ControlsStateEvent(controlsState));
}

void Presentation::SetViewPort(int width, int height) {
    video_->SetViewPort(width, height);
}

void Presentation::RenderFrame() {
    eventLoop_->RunUntilEventOfType(&frameGeneratedEvent_.Type());
}

}
}

