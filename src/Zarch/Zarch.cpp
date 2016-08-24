#include <Zarch/Zarch.h>

#include <kxm/Core/Thread.h>
#include <Game/EventLoop.h>
#include <Game/EventLoopHub.h>
#include <Zarch/Simulation.h>
#include <Zarch/Presentation.h>
#include <Zarch/ControlsState.h>
#include <Zarch/Events/FrameTimeEvent.h>
#include <Zarch/Events/FrameGeneratedEvent.h>
#include <Zarch/Events/ControlsStateEvent.h>
#include <Zarch/Events/LanderMoveEvent.h>
#include <Zarch/Events/LanderVelocityEvent.h>
#include <Zarch/Events/LanderThrusterEvent.h>

using namespace std;
using namespace kxm::Core;
using namespace kxm::Vectoid;
using namespace kxm::Game;

namespace kxm {
namespace Zarch {

Zarch::Zarch(shared_ptr<ThreadingFactoryInterface> threadingFactory) {
    threadingFactory_ = threadingFactory;
    eventLoopHub_     = shared_ptr<EventLoopHub>(new EventLoopHub());
    simulation_       = shared_ptr<Simulation>(new Simulation(eventLoopHub_));
    presentation_     = shared_ptr<Presentation>(new Presentation(eventLoopHub_));
    simulationThread_ = shared_ptr<Thread>(new Thread(simulation_, *threadingFactory_));
}

Zarch::~Zarch() {
    eventLoopHub_->RequestShutdown();
}

void Zarch::RegisterEvents(Game::EventLoop<ZarchEvent, EventHandlerCore> *eventLoop) {
    eventLoop->RegisterEvent(unique_ptr<ZarchEvent>(new FrameTimeEvent));
    eventLoop->RegisterEvent(unique_ptr<ZarchEvent>(new FrameGeneratedEvent));
    eventLoop->RegisterEvent(unique_ptr<ZarchEvent>(new ControlsStateEvent));
    eventLoop->RegisterEvent(unique_ptr<ZarchEvent>(new LanderMoveEvent));
    eventLoop->RegisterEvent(unique_ptr<ZarchEvent>(new LanderVelocityEvent));
    eventLoop->RegisterEvent(unique_ptr<ZarchEvent>(new LanderThrusterEvent));
}

}    // Namespace Zarch.
}    // Namespace kxm.
