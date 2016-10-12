#include <kxm/Zarch/Simulation.h>

#include <kxm/Core/logging.h>
#include <kxm/Game/EventLoop.h>
#include <kxm/Zarch/Zarch.h>
#include <kxm/Zarch/AI/AI.h>
#include <kxm/Zarch/GameLogic/GameLogic.h>
#include <kxm/Zarch/Physics/Physics.h>
#include <kxm/Zarch/Events/InitializationEvent.h>
#include <kxm/Zarch/Events/TriggerEvent.h>

using namespace std;
using namespace std::chrono;
using namespace kxm::Core;
using namespace kxm::Game;

namespace kxm {
namespace Zarch {

Simulation::Simulation(const shared_ptr<EventLoopHub> &eventLoopHub)
        : eventLoop_(new EventLoop<ZarchEvent, EventHandlerCore>(eventLoopHub)),
          lastUpdateTime_(steady_clock::now()),
          simulationUpdated_(false),
          frameRendered_(false) {
    Zarch::RegisterEvents(eventLoop_.get());
    ai_        = make_shared<AI::AI>(eventLoop_, TriggerEvent::AITrigger, TriggerEvent::GameLogicTrigger);
    gameLogic_ = make_shared<GameLogic::GameLogic>(eventLoop_,
                                                   TriggerEvent::GameLogicTrigger, TriggerEvent::PhysicsTrigger);
    physics_   = make_shared<Physics::Physics>(eventLoop_,
                                               TriggerEvent::PhysicsTrigger, TriggerEvent::SimulationUpdatedTrigger);
    
    eventLoop_->RegisterHandler(InitializationEvent::type, this);
    eventLoop_->RegisterHandler(TriggerEvent::type,        this);
}

Simulation::~Simulation() {
    eventLoop_->UnregisterHandlers();
}

void Simulation::ExecuteAction() {
    puts("simulation thread spawned");
    eventLoop_->Post(InitializationEvent());
    eventLoop_->Run();
    puts("simulation thread terminating");
}

void Simulation::Handle(const InitializationEvent &event) {
    eventLoop_->Post(TriggerEvent(TriggerEvent::SimulationUpdatedTrigger, 0.0f));
    eventLoop_->Post(TriggerEvent(TriggerEvent::FrameRenderedTrigger, 0.0f));
}

void Simulation::Handle(const TriggerEvent &event) {
    switch (event.trigger) {
        case TriggerEvent::FrameRenderedTrigger:
            frameRendered_ = true;
            break;
        case TriggerEvent::SimulationUpdatedTrigger:
            simulationUpdated_ = true;
            break;
        default:
            return;
    }
    DoSimulationTrigger();
}

void Simulation::DoSimulationTrigger() {
    if (simulationUpdated_ && frameRendered_) {
        auto now = steady_clock::now();
        int milliSeconds = (int)duration_cast<milliseconds>(now - lastUpdateTime_).count();
        lastUpdateTime_ = now;
        eventLoop_->Post(TriggerEvent(TriggerEvent::AITrigger, (float)milliSeconds / 1000.0f));
        
        simulationUpdated_ = false;
        frameRendered_     = false;
    }
}

}
}

