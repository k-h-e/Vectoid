//
//  Simulation.cpp
//  kxm
//
//  Created by Kai Hergenröther on 4/7/13.
//
//


#include <Zarch/Simulation.h>

#include <kxm/Core/logging.h>
#include <Game/EventLoop.h>
#include <Game/Processes.h>
#include <Zarch/Zarch.h>
#include <Zarch/GameLogic/GameLogic.h>
#include <Zarch/Physics/Physics.h>
#include <Zarch/Events/FrameTimeEvent.h>


using namespace std;
using namespace kxm::Core;
using namespace kxm::Game;


namespace kxm {
namespace Zarch {

Simulation::Simulation(const shared_ptr<EventLoopHub> &eventLoopHub)
        : eventLoop_(new EventLoop<ZarchEvent, EventHandlerCore>(eventLoopHub)),
          processes_(new Processes()) {
    Zarch::RegisterEvents(eventLoop_.get());
        
    physics_   = shared_ptr<Physics>(new Physics(eventLoop_, processes_));
    for (Event::EventType eventType : physics_->EnumerateHandledEvents()) {
        eventLoop_->RegisterHandler(eventType, physics_.get());
    }
    gameLogic_ = shared_ptr<GameLogic>(new GameLogic(eventLoop_, processes_));
    for (Event::EventType eventType : gameLogic_->EnumerateHandledEvents()) {
        eventLoop_->RegisterHandler(eventType, gameLogic_.get());
    }
}

Simulation::~Simulation() {
    eventLoop_->UnregisterHandler(physics_.get());
    processes_->UnregisterProcesses(physics_.get());
    
    eventLoop_->UnregisterHandler(gameLogic_.get());
    processes_->UnregisterProcesses(gameLogic_.get());
}

void Simulation::ExecuteAction() {
    puts("simulation thread spawned");
    eventLoop_->Run();
    puts("simulation thread terminating");
}

}
}

