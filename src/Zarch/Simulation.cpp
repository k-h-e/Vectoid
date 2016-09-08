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
#include <Zarch/Events/InitializationEvent.h>
#include <Zarch/Events/UpdatePhysicsEvent.h>
#include <Zarch/Events/PhysicsUpdatedEvent.h>

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
    physics_   = shared_ptr<Physics::Physics>(new Physics::Physics(eventLoop_));
    gameLogic_ = shared_ptr<GameLogic::GameLogic>(new GameLogic::GameLogic(eventLoop_));
    
    eventLoop_->RegisterHandler(InitializationEvent::type, this);
    eventLoop_->RegisterHandler(PhysicsUpdatedEvent::type, this);
    eventLoop_->RegisterHandler(FrameGeneratedEvent::type, this);
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
    eventLoop_->Post(PhysicsUpdatedEvent());
    eventLoop_->Post(FrameGeneratedEvent());
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

