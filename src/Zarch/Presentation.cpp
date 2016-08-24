#include <Zarch/Presentation.h>

#include <kxm/Core/logging.h>
#include <Game/EventLoop.h>
#include <Game/Processes.h>
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
        : eventLoop_(new EventLoop<ZarchEvent, EventHandlerCore>(eventLoopHub)),
          processes_(new Processes()) {
    Zarch::RegisterEvents(eventLoop_.get());
    
    video_ = shared_ptr<Video>(new Video(eventLoop_, processes_));
    for (Event::EventType eventType : video_->EnumerateHandledEvents()) {
        eventLoop_->RegisterHandler(eventType, video_.get());
    }
              
    eventLoop_->Schedule(FrameGeneratedEvent());
}

Presentation::~Presentation() {
    eventLoop_->UnregisterHandler(video_.get());
    processes_->UnregisterProcesses(video_.get());
}

void Presentation::PrepareFrame(const ControlsState &controlsState) {
    eventLoop_->Schedule(ControlsStateEvent(controlsState));
    processes_->ExecuteProcesses();
}

void Presentation::SetViewPort(int width, int height) {
    video_->SetViewPort(width, height);
}

void Presentation::RenderFrame() {
    eventLoop_->RunUntilEventOfType(&frameGeneratedEvent_.Type());
}

}
}

