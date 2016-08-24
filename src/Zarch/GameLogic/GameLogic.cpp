#include <Zarch/GameLogic/GameLogic.h>

#include <kxm/Core/logging.h>
#include <Game/EventLoop.h>
#include <Game/ProcessesClientInterface.h>
#include <Zarch/Events/ZarchEvent.h>
#include <Zarch/Events/ControlsStateEvent.h>
#include <Zarch/Events/FrameTimeEvent.h>
#include <Zarch/Events/FrameGeneratedEvent.h>

using namespace std;
using namespace std::chrono;
using namespace kxm::Core;
using namespace kxm::Game;

namespace kxm {
namespace Zarch {

GameLogic::GameLogic(shared_ptr<EventLoop<ZarchEvent, EventHandlerCore>> eventLoop,
                     shared_ptr<ProcessesClientInterface> processes)
        : eventLoop_(eventLoop),
          processes_(processes),
          landerThrusterEnabled_(false),
          landerFiringEnabled_(false),
          lastFrameTime_(steady_clock::now()) {
    // Nop.
}

GameLogic::~GameLogic() {
    // Nop.
}

vector<Event::EventType> GameLogic::EnumerateHandledEvents() {
    return vector<Event::EventType>{ ControlsStateEvent::type,
                                     FrameGeneratedEvent::type };
}

void GameLogic::HandleProcessFinished(ProcessInterface *process) {
    // Nop.
}

void GameLogic::HandleFrameGeneratedEvent(const FrameGeneratedEvent &event) {
    auto now = steady_clock::now();
    int milliSeconds = (int)duration_cast<milliseconds>(now - lastFrameTime_).count();
    lastFrameTime_ = now;
    float frameDeltaTimeS = (float)milliSeconds / 1000.0f;
    eventLoop_->Schedule(FrameTimeEvent(frameDeltaTimeS));
}
    
void GameLogic::HandleControlsStateEvent(const ControlsStateEvent &event) {
    // Nop.
}

}    // Namespace Zarch.
}    // Namespace kxm.

