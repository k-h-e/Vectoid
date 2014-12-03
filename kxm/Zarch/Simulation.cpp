//
//  Simulation.cpp
//  kxm
//
//  Created by Kai Hergenröther on 4/7/13.
//
//


#include <kxm/Zarch/Simulation.h>

#include <kxm/Core/logging.h>
#include <kxm/Zarch/Zarch.h>
#include <kxm/Zarch/GameLogic/GameLogic.h>
#include <kxm/Zarch/Physics/Physics.h>
#include <kxm/Zarch/Events/FrameTimeEvent.h>
#include <kxm/Zarch/Events/ControlsStateEvent.h>


using namespace std;
using namespace std::chrono;
using namespace kxm::Core;
using namespace kxm::Game;


namespace kxm {
namespace Zarch {

Simulation::Simulation(const shared_ptr<EventQueueHub> &eventQueueHub)
        : eventQueue_(EventQueueHub::initialBufferSize),
          eventQueueHub_(eventQueueHub),
          processes_(new Processes<ZarchProcess::ProcessType>()),
          processContext_(*processes_, eventQueue_),
          lastFrameTime_(steady_clock::now()) {
    Zarch::RegisterEvents(&eventQueue_);
    
    physics_ = shared_ptr<Physics>(new Physics(processes_));
    eventQueue_.AddHandler(FrameTimeEvent::type, physics_);
    eventQueue_.AddHandler(ControlsStateEvent::type, physics_);
    
    gameLogic_ = shared_ptr<GameLogic>(new GameLogic());
    eventQueue_.AddHandler(ControlsStateEvent::type, gameLogic_);

    hubClientId_ = eventQueueHub_->AllocUniqueClientId();
}

void Simulation::ExecuteAction() {
    puts("simulation thread spawned");
    
    bool shutdownRequested = false;
    while (!shutdownRequested) {
        shutdownRequested = !eventQueue_.SyncWithHub(eventQueueHub_.get(), hubClientId_, true);
        GenerateTimeEvent();
        eventQueue_.ProcessEvents();
        
        processes_->ExecuteProcesses(processContext_);
    }
    
    puts("simulation thread terminating");
}

void Simulation::GenerateTimeEvent() {
    auto now = steady_clock::now();
    int milliSeconds = (int)duration_cast<milliseconds>(now - lastFrameTime_).count();
    lastFrameTime_ = now;
    float frameDeltaTimeS = (float)milliSeconds / 1000.0f;
    processContext_.eventQueue.Schedule(FrameTimeEvent(frameDeltaTimeS));
}

}
}

