#include <Zarch/GameLogic/GameLogic.h>

#include <kxm/Core/logging.h>
#include <Game/EventLoop.h>
#include <Zarch/Events/ZarchEvent.h>
#include <Zarch/Events/InitializationEvent.h>
#include <Zarch/Events/ActorCreatedEvent.h>
#include <Zarch/Events/FrameTimeEvent.h>
#include <Zarch/Events/FrameGeneratedEvent.h>

using namespace std;
using namespace std::chrono;
using namespace kxm::Core;
using namespace kxm::Game;

namespace kxm {
namespace Zarch {

GameLogic::GameLogic(shared_ptr<EventLoop<ZarchEvent, EventHandlerCore>> eventLoop)
        : eventLoop_(eventLoop),
          landerThrusterEnabled_(false),
          landerFiringEnabled_(false),
          lastFrameTime_(steady_clock::now()) {
    eventLoop_->RegisterHandler(InitializationEvent::type,  this);
    eventLoop_->RegisterHandler(FrameGeneratedEvent::type, this);
}

GameLogic::~GameLogic() {
    // Nop.
}

void GameLogic::HandleProcessFinished(ProcessInterface *process) {
    // Nop.
}

void GameLogic::Handle(const InitializationEvent &event) {
    PrepareMap();
}

void GameLogic::Handle(const FrameGeneratedEvent &event) {
    auto now = steady_clock::now();
    int milliSeconds = (int)duration_cast<milliseconds>(now - lastFrameTime_).count();
    lastFrameTime_ = now;
    float frameDeltaTimeS = (float)milliSeconds / 1000.0f;
    eventLoop_->Post(FrameTimeEvent(frameDeltaTimeS));
}

void GameLogic::PrepareMap() {
    ActorId landerActor = actorNaming_.Get();
    eventLoop_->Post(ActorCreatedEvent(landerActor, LanderActor));
    
    actorNaming_.Put(landerActor);
    actorNaming_.Put(landerActor);
    
    landerActor = actorNaming_.Get();
    eventLoop_->Post(ActorCreatedEvent(landerActor, LanderActor));
    
    landerActor = actorNaming_.Get();
    eventLoop_->Post(ActorCreatedEvent(landerActor, LanderActor));
}

}    // Namespace Zarch.
}    // Namespace kxm.

