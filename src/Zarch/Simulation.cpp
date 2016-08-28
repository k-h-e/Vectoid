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
#include <Zarch/Zarch.h>
#include <Zarch/GameLogic/GameLogic.h>
#include <Zarch/Physics/Physics.h>
#include <Zarch/Events/UpdatePhysicsEvent.h>
#include <Zarch/Events/PhysicsUpdatedEvent.h>
#include <Zarch/Events/FrameTimeEvent.h>


using namespace std;
using namespace kxm::Core;
using namespace kxm::Game;


namespace kxm {
namespace Zarch {

Simulation::Simulation(const shared_ptr<EventLoopHub> &eventLoopHub)
        : eventLoop_(new EventLoop<ZarchEvent, EventHandlerCore>(eventLoopHub)),
          physicsUpdated_(false),
          frameGenerated_(false) {
    Zarch::RegisterEvents(eventLoop_.get());
    physics_   = shared_ptr<Physics>(new Physics(eventLoop_));
    gameLogic_ = shared_ptr<GameLogic>(new GameLogic(eventLoop_));
    
    eventLoop_->RegisterHandler(PhysicsUpdatedEvent::type, this);
    eventLoop_->RegisterHandler(FrameGeneratedEvent::type, this);
}

Simulation::~Simulation() {
    eventLoop_->UnregisterHandlers();
}

void Simulation::ExecuteAction() {
    puts("simulation thread spawned");
    
    // Post initial events...
    eventLoop_->Post(PhysicsUpdatedEvent());
    eventLoop_->Post(FrameGeneratedEvent());
    
    eventLoop_->Run();
    
    puts("simulation thread terminating");
}

void Simulation::Handle(const PhysicsUpdatedEvent &event) {
    physicsUpdated_ = true;
    DoPhysicsTrigger();
}
void Simulation::Handle(const FrameGeneratedEvent &event) {
    frameGenerated_ = true;
    DoPhysicsTrigger();
}
void Simulation::DoPhysicsTrigger() {
    if (physicsUpdated_ && frameGenerated_) {
        physicsUpdated_ = false;
        frameGenerated_ = false;
        eventLoop_->Post(UpdatePhysicsEvent());
    }
}

}
}

