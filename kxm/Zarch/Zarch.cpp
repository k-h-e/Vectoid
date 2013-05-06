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
#include <kxm/Game/ThreadCouplingBuffer.h>
#include <kxm/Zarch/Simulation.h>
#include <kxm/Zarch/Presentation.h>
#include <kxm/Zarch/ControlsState.h>
#include <kxm/Zarch/events.h>

using namespace boost;
using namespace kxm::Core;
using namespace kxm::Vectoid;
using namespace kxm::Game;


namespace kxm {
namespace Zarch {

Zarch::Zarch(shared_ptr<ThreadingFactoryInterface> threadingFactory) {
    threadingFactory_         = threadingFactory;
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

void Zarch::RegisterEvents(EventQueue<ZarchEvent::EventType> *eventQueue) {
    shared_ptr<Pool<Event, PayloadEvent<Vector> > >
        vectorEventPool(new Pool<Event, PayloadEvent<Vector> >());
    shared_ptr<Pool<Event, PayloadEvent<Transform> > >
        transformEventPool(new Pool<Event, PayloadEvent<Transform> >());
    shared_ptr<Pool<Event, PayloadEvent<Variant> > >
        variantEventPool(new Pool<Event, PayloadEvent<Variant> >());
    shared_ptr<Pool<Event, PayloadEvent<ControlsState> > >
        controlsStateEventPool(new Pool<Event, PayloadEvent<ControlsState> >());
    int vectorEventPoolId        = eventQueue->RegisterEventPool(vectorEventPool),
        transformEventPoolId     = eventQueue->RegisterEventPool(transformEventPool),
        variantEventPoolId       = eventQueue->RegisterEventPool(variantEventPool),
        controlsStateEventPoolId = eventQueue->RegisterEventPool(controlsStateEventPool);
    
    eventQueue->RegisterEventType(ZarchEvent::FrameTimeEvent,      variantEventPoolId);
    eventQueue->RegisterEventType(ZarchEvent::ControlsStateEvent,  controlsStateEventPoolId);
    eventQueue->RegisterEventType(ZarchEvent::LanderMoveEvent,     transformEventPoolId);
    eventQueue->RegisterEventType(ZarchEvent::LanderVelocityEvent, vectorEventPoolId);
    eventQueue->RegisterEventType(ZarchEvent::LanderThrusterEvent, variantEventPoolId);
}

}    // Namespace Zarch.
}    // Namespace kxm.
