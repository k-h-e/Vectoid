#include <Zarch/Zarch.h>

#include <Game/EventLoop.h>
#include <Game/EventLoopHub.h>
#include <Zarch/Simulation.h>
#include <Zarch/Presentation.h>
#include <Zarch/ControlsState.h>
#include <Zarch/Events/InitializationEvent.h>
#include <Zarch/Events/ActorCreationEvent.h>
#include <Zarch/Events/ActorTerminationEvent.h>
#include <Zarch/Events/MoveEvent.h>
#include <Zarch/Events/VelocityEvent.h>
#include <Zarch/Events/PhysicsOverrideEvent.h>
#include <Zarch/Events/AccelerationEvent.h>
#include <Zarch/Events/ControlsEvent.h>
#include <Zarch/Events/FrameGeneratedEvent.h>
#include <Zarch/Events/UpdatePhysicsEvent.h>
#include <Zarch/Events/PhysicsUpdatedEvent.h>

using namespace std;
using namespace kxm::Core;
using namespace kxm::Vectoid;
using namespace kxm::Game;

namespace kxm {
namespace Zarch {

Zarch::Zarch() {
    eventLoopHub_ = shared_ptr<EventLoopHub>(new EventLoopHub());
    simulation_   = shared_ptr<Simulation>(new Simulation(eventLoopHub_));
    presentation_ = shared_ptr<Presentation>(new Presentation(eventLoopHub_));
    
    auto simulation = simulation_;
    simulationThread_ = shared_ptr<thread>(new thread([simulation]{ simulation->ExecuteAction(); }));
    std::printf("joinable=%d\n", (int)simulationThread_->joinable());
}

Zarch::~Zarch() {
    eventLoopHub_->RequestShutdown();
    simulationThread_->join();
}

void Zarch::RegisterEvents(Game::EventLoop<ZarchEvent, EventHandlerCore> *eventLoop) {
    eventLoop->RegisterEvent(unique_ptr<ZarchEvent>(new InitializationEvent));
    eventLoop->RegisterEvent(unique_ptr<ZarchEvent>(new ActorCreationEvent));
    eventLoop->RegisterEvent(unique_ptr<ZarchEvent>(new ActorTerminationEvent));
    eventLoop->RegisterEvent(unique_ptr<ZarchEvent>(new MoveEvent));
    eventLoop->RegisterEvent(unique_ptr<ZarchEvent>(new VelocityEvent));
    eventLoop->RegisterEvent(unique_ptr<ZarchEvent>(new PhysicsOverrideEvent));
    eventLoop->RegisterEvent(unique_ptr<ZarchEvent>(new AccelerationEvent));
    eventLoop->RegisterEvent(unique_ptr<ZarchEvent>(new ControlsEvent));
    eventLoop->RegisterEvent(unique_ptr<ZarchEvent>(new FrameGeneratedEvent));
    eventLoop->RegisterEvent(unique_ptr<ZarchEvent>(new UpdatePhysicsEvent));
    eventLoop->RegisterEvent(unique_ptr<ZarchEvent>(new PhysicsUpdatedEvent));
}

}    // Namespace Zarch.
}    // Namespace kxm.
