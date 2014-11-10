//
//  Zarch.cpp
//  kxm
//
//  Created by Kai Hergenröther on 12/3/12.
//
//


#include <kxm/Zarch/Zarch.h>

#include <kxm/Core/Thread.h>
#include <kxm/Game/Pool.h>
#include <kxm/Game/EventQueueHub.h>
#include <kxm/Game/ThreadCouplingBuffer.h>
#include <kxm/Zarch/Simulation.h>
#include <kxm/Zarch/Presentation.h>
#include <kxm/Zarch/ControlsState.h>
#include <kxm/Zarch/events.h>
#include <kxm/Zarch/Events/FrameTimeEvent.h>
#include <kxm/Zarch/Events/ControlsStateEvent.h>
#include <kxm/Zarch/Events/LanderMoveEvent.h>
#include <kxm/Zarch/Events/LanderVelocityEvent.h>
#include <kxm/Zarch/Events/LanderThrusterEvent.h>

using namespace std;
using namespace kxm::Core;
using namespace kxm::Vectoid;
using namespace kxm::Game;


namespace kxm {
namespace Zarch {

Zarch::Zarch(shared_ptr<ThreadingFactoryInterface> threadingFactory) {
    threadingFactory_         = threadingFactory;
    eventQueueHub_            = shared_ptr<EventQueueHub>(new EventQueueHub());
    simulationCouplingBuffer_ = shared_ptr<ThreadCouplingBuffer>(
                                    new ThreadCouplingBuffer(*threadingFactory_));
    simulation_               = shared_ptr<Simulation>(
                                    new Simulation(simulationCouplingBuffer_, 0));
    presentation_             = shared_ptr<Presentation>(
                                    new Presentation(simulationCouplingBuffer_, 1));
    
    simulationThread_         = shared_ptr<Thread>(new Thread(simulation_, *threadingFactory_));
}

Zarch::~Zarch() {
    // Ask simulation thread to shut down. It will be joined when our member thread object gets
    // destroyed.
    ThreadCouplingBuffer::Accessor accessor = simulationCouplingBuffer_->Access(0);
    accessor.RequestShutdown();
}

void Zarch::RegisterEvents(OldEventQueue<OldZarchEvent::EventType> *eventQueue) {
    shared_ptr<Pool<Game::OldEvent, OldEvent<Vector>>>
        vectorEventPool(new Pool<Game::OldEvent, OldEvent<Vector>>());
    shared_ptr<Pool<Game::OldEvent, OldEvent<Transform>>>
        transformEventPool(new Pool<Game::OldEvent, OldEvent<Transform>>());
    shared_ptr<Pool<Game::OldEvent, OldEvent<Variant>>>
        variantEventPool(new Pool<Game::OldEvent, OldEvent<Variant>>());
    shared_ptr<Pool<Game::OldEvent, OldEvent<ControlsState>>>
        controlsStateEventPool(new Pool<Game::OldEvent, OldEvent<ControlsState>>());
    int vectorEventPoolId        = eventQueue->RegisterEventPool(vectorEventPool),
        transformEventPoolId     = eventQueue->RegisterEventPool(transformEventPool),
        variantEventPoolId       = eventQueue->RegisterEventPool(variantEventPool),
        controlsStateEventPoolId = eventQueue->RegisterEventPool(controlsStateEventPool);
    
    eventQueue->RegisterEventType(OldZarchEvent::FrameTimeEvent,      variantEventPoolId);
    eventQueue->RegisterEventType(OldZarchEvent::ControlsStateEvent,  controlsStateEventPoolId);
    eventQueue->RegisterEventType(OldZarchEvent::LanderMoveEvent,     transformEventPoolId);
    eventQueue->RegisterEventType(OldZarchEvent::LanderVelocityEvent, vectorEventPoolId);
    eventQueue->RegisterEventType(OldZarchEvent::LanderThrusterEvent, variantEventPoolId);
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
