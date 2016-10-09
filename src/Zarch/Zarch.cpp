#include <kxm/Zarch/Zarch.h>

#include <kxm/Game/EventLoop.h>
#include <kxm/Game/EventLoopHub.h>
#include <kxm/Zarch/Simulation.h>
#include <kxm/Zarch/Presentation.h>
#include <kxm/Zarch/ControlsState.h>
#include <kxm/Zarch/Events/InitializationEvent.h>
#include <kxm/Zarch/Events/TimeEvent.h>
#include <kxm/Zarch/Events/ActorCreationEvent.h>
#include <kxm/Zarch/Events/ActorTerminationEvent.h>
#include <kxm/Zarch/Events/MoveEvent.h>
#include <kxm/Zarch/Events/VelocityEvent.h>
#include <kxm/Zarch/Events/PhysicsOverrideEvent.h>
#include <kxm/Zarch/Events/AccelerationEvent.h>
#include <kxm/Zarch/Events/ControlsRequestEvent.h>
#include <kxm/Zarch/Events/ControlsEvent.h>
#include <kxm/Zarch/Events/ControlsRejectionEvent.h>
#include <kxm/Zarch/Events/OldControlsEvent.h>
#include <kxm/Zarch/Events/FrameGeneratedEvent.h>
#include <kxm/Zarch/Events/UpdatePhysicsEvent.h>
#include <kxm/Zarch/Events/PhysicsUpdatedEvent.h>

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
}

Zarch::~Zarch() {
    eventLoopHub_->RequestShutdown();
    simulationThread_->join();
}

void Zarch::RegisterEvents(Game::EventLoop<ZarchEvent, EventHandlerCore> *eventLoop) {
    eventLoop->RegisterEvent(unique_ptr<ZarchEvent>(new InitializationEvent));
    eventLoop->RegisterEvent(unique_ptr<ZarchEvent>(new TimeEvent));
    eventLoop->RegisterEvent(unique_ptr<ZarchEvent>(new ActorCreationEvent));
    eventLoop->RegisterEvent(unique_ptr<ZarchEvent>(new ActorTerminationEvent));
    eventLoop->RegisterEvent(unique_ptr<ZarchEvent>(new MoveEvent));
    eventLoop->RegisterEvent(unique_ptr<ZarchEvent>(new VelocityEvent));
    eventLoop->RegisterEvent(unique_ptr<ZarchEvent>(new PhysicsOverrideEvent));
    eventLoop->RegisterEvent(unique_ptr<ZarchEvent>(new AccelerationEvent));
    eventLoop->RegisterEvent(unique_ptr<ZarchEvent>(new ControlsRequestEvent));
    eventLoop->RegisterEvent(unique_ptr<ZarchEvent>(new ControlsEvent));
    eventLoop->RegisterEvent(unique_ptr<ZarchEvent>(new ControlsRejectionEvent));
    eventLoop->RegisterEvent(unique_ptr<ZarchEvent>(new OldControlsEvent));
    eventLoop->RegisterEvent(unique_ptr<ZarchEvent>(new FrameGeneratedEvent));
    eventLoop->RegisterEvent(unique_ptr<ZarchEvent>(new UpdatePhysicsEvent));
    eventLoop->RegisterEvent(unique_ptr<ZarchEvent>(new PhysicsUpdatedEvent));
}

}    // Namespace Zarch.
}    // Namespace kxm.
