//
//  Zarch.cpp
//  kxm
//
//  Created by Kai Hergenröther on 12/3/12.
//
//


#include <Zarch/Zarch.h>

#include <kxm/Core/Thread.h>
#include <Game/Pool.h>
#include <Game/EventQueueHub.h>
#include <Zarch/Simulation.h>
#include <Zarch/Presentation.h>
#include <Zarch/ControlsState.h>
#include <Zarch/Events/FrameTimeEvent.h>
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
    threadingFactory_         = threadingFactory;
    eventQueueHub_            = shared_ptr<EventQueueHub>(new EventQueueHub());
    simulation_               = shared_ptr<Simulation>(new Simulation(eventQueueHub_));
    presentation_             = shared_ptr<Presentation>(new Presentation(eventQueueHub_));
    simulationThread_         = shared_ptr<Thread>(new Thread(simulation_, *threadingFactory_));
}

Zarch::~Zarch() {
    // Ask simulation thread to shut down. It will be joined when our member thread object gets
    // destroyed.
    eventQueueHub_->RequestShutdown();
}

void Zarch::RegisterEvents(Game::EventQueue *eventQueue) {
    eventQueue->RegisterEvent(unique_ptr<Event>(new FrameTimeEvent));
    eventQueue->RegisterEvent(unique_ptr<Event>(new ControlsStateEvent));
    eventQueue->RegisterEvent(unique_ptr<Event>(new LanderMoveEvent));
    eventQueue->RegisterEvent(unique_ptr<Event>(new LanderVelocityEvent));
    eventQueue->RegisterEvent(unique_ptr<Event>(new LanderThrusterEvent));
}

}    // Namespace Zarch.
}    // Namespace kxm.
