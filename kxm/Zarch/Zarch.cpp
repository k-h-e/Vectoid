//
//  Zarch.cpp
//  kxm
//
//  Created by Kai Hergenröther on 12/3/12.
//
//


#include <kxm/Zarch/Zarch.h>

#include <kxm/Core/logging.h>
#include <kxm/Core/ThreadingFactoryInterface.h>
#include <kxm/Core/Thread.h>
#include <kxm/Vectoid/PerspectiveProjection.h>
#include <kxm/Vectoid/Camera.h>
#include <kxm/Vectoid/CoordSys.h>
#include <kxm/Vectoid/Geode.h>
#include <kxm/Vectoid/Particles.h>
#include <kxm/Vectoid/ParticlesRenderer.h>
#include <kxm/Vectoid/AgeColoredParticles.h>
#include <kxm/Game/Pool.h>
#include <kxm/Game/ThreadCouplingBuffer.h>
#include <kxm/Zarch/Video/TerrainRenderer.h>
#include <kxm/Zarch/Simulation.h>
#include <kxm/Zarch/Presentation.h>
#include <kxm/Zarch/Terrain.h>
#include <kxm/Zarch/LanderGeometry.h>
#include <kxm/Zarch/MapParameters.h>
#include <kxm/Zarch/ControlsState.h>
#include <kxm/Zarch/events.h>

using namespace std;
using namespace kxm::Core;
using namespace kxm::Vectoid;
using namespace kxm::Game;

using boost::shared_ptr;


namespace kxm {
namespace Zarch {

Zarch::Zarch(shared_ptr<ThreadingFactoryInterface> threadingFactory) {
    mapParameters_ = shared_ptr<MapParameters>(new MapParameters());
    
    // Create scene graph...
    projection_ = shared_ptr<PerspectiveProjection>(new PerspectiveProjection());
    projection_->SetWindowSize(11.0f);
    projection_->SetViewingDepth(11.0f);
    projection_->SetEyepointDistance(11.0f);
    shared_ptr<Camera> camera(new Camera());
    projection_->AddChild(camera);
    shared_ptr<CoordSys> landerCoordSys(new CoordSys());
    camera->AddChild(landerCoordSys);
    shared_ptr<LanderGeometry> landerGeometry(new LanderGeometry());
    landerCoordSys->AddChild(shared_ptr<Geode>(new Geode(landerGeometry)));
    shared_ptr<Terrain> terrain(new Terrain(mapParameters_));
    shared_ptr<TerrainRenderer> terrainRenderer(new TerrainRenderer(terrain, mapParameters_));
    camera->AddChild(shared_ptr<Geode>(new Geode(terrainRenderer)));
    shared_ptr<Particles> thrusterParticles(new Particles()),
                          shotsParticles(new Particles()),
                          starFieldParticles(new Particles());
    camera->AddChild(shared_ptr<Geode>(new Geode(shared_ptr<AgeColoredParticles>(
        new AgeColoredParticles(thrusterParticles)))));
    camera->AddChild(shared_ptr<Geode>(new Geode(shared_ptr<ParticlesRenderer>(
        new ParticlesRenderer(shotsParticles)))));
    camera->AddChild(shared_ptr<Geode>(new Geode(shared_ptr<ParticlesRenderer>(
        new ParticlesRenderer(starFieldParticles)))));
    
    // Install subsystems...
    gameLogic_ = shared_ptr<GameLogic>(new GameLogic());
    physics_   = shared_ptr<Physics>(
                     new Physics(&eventQueue_, mapParameters_, terrain, landerCoordSys,
                     thrusterParticles, shotsParticles));
    video_     = shared_ptr<Video>(
                     new Video(&eventQueue_, mapParameters_, camera, terrainRenderer,
                               starFieldParticles));
    
    RegisterEvents(&eventQueue_);
        
    // Register event handlers...
    eventQueue_.RegisterEventHandler(ZarchEvent::FrameTimeEvent, physics_);
    eventQueue_.RegisterEventHandler(ZarchEvent::ControlsStateEvent, physics_);
    eventQueue_.RegisterEventHandler(ZarchEvent::LanderMoveEvent, video_);
    
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
    // TODO : Ask simulation thread to shut down.
}

void Zarch::Execute(const FrameTimeProcess::FrameTimeInfo &timeInfo,
                    const ControlsState &controlsState) {
    static_cast<PayloadEvent<Variant> &>(eventQueue_.ScheduleEvent(ZarchEvent::FrameTimeEvent))
        .Data().Reset(timeInfo.timeSinceLastFrame);
    static_cast<PayloadEvent<ControlsState> &>(eventQueue_.ScheduleEvent(ZarchEvent::ControlsStateEvent))
        .Reset(controlsState);
    
    physics_->ExecuteProcesses();
    eventQueue_.ProcessEvents();
    video_->ExecuteProcesses();
    
    gameLogic_->ExecuteProcesses();
    
    
    presentation_->PrepareFrame(controlsState);
}

void Zarch::SetViewPort(int width, int height) {
    projection_->SetViewPort((float)width, (float)height);
    Log().Stream() << "viewport set" << ", size=(" << (int)width << "," << (int)height << ")"
                   << endl;
    
    presentation_->SetViewPort(width, height);
}

void Zarch::RenderFrame() {
    //projection_->Render(0);
    
    presentation_->RenderFrame();
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
