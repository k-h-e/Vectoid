//
//  Zarch.cpp
//  kxm
//
//  Created by Kai Hergenröther on 12/3/12.
//
//


#include <kxm/Zarch/Zarch.h>

#include <kxm/Core/logging.h>
#include <kxm/Vectoid/PerspectiveProjection.h>
#include <kxm/Vectoid/Camera.h>
#include <kxm/Vectoid/CoordSys.h>
#include <kxm/Vectoid/Geode.h>
#include <kxm/Vectoid/Particles.h>
#include <kxm/Vectoid/ParticlesRenderer.h>
#include <kxm/Vectoid/AgeColoredParticles.h>
#include <kxm/Game/Pool.h>
#include <kxm/Game/ThreadCouplingBuffer.h>
#include <kxm/Zarch/Simulation.h>
#include <kxm/Zarch/Presentation.h>
#include <kxm/Zarch/MapParameters.h>
#include <kxm/Zarch/Terrain.h>
#include <kxm/Zarch/LanderGeometry.h>
#include <kxm/Zarch/Video/TerrainRenderer.h>
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
    gameLogic_ = boost::shared_ptr<GameLogic>(new GameLogic());
    physics_   = boost::shared_ptr<Physics>(
                     new Physics(&eventQueue_, mapParameters_, terrain, landerCoordSys,
                                 thrusterParticles, shotsParticles));
    video_     = boost::shared_ptr<Video>(
                     new Video(&eventQueue_, mapParameters_, camera, terrainRenderer,
                               starFieldParticles));
    
    // Register event types...
    shared_ptr<Pool<Event, TransformEvent> >     transformEventPool(
                                                     new Pool<Event, TransformEvent>());
    shared_ptr<Pool<Event, VariantEvent> >       variantEventPool(
                                                     new Pool<Event, VariantEvent>());
    shared_ptr<Pool<Event, ControlsStateEvent> > controlsStateEventPool(
                                                     new Pool<Event, ControlsStateEvent>());
    int transformEventPoolId     = eventQueue_.RegisterEventPool(transformEventPool),
        variantEventPoolId       = eventQueue_.RegisterEventPool(variantEventPool),
        controlsStateEventPoolId = eventQueue_.RegisterEventPool(controlsStateEventPool);
    eventQueue_.RegisterEventType(ZarchEvent::FrameTimeEvent, variantEventPoolId);
    eventQueue_.RegisterEventType(ZarchEvent::ControlsStateEvent, controlsStateEventPoolId);
    eventQueue_.RegisterEventType(ZarchEvent::LanderMovedEvent, transformEventPoolId);
    
    // Register event handlers...
    eventQueue_.RegisterEventHandler(ZarchEvent::FrameTimeEvent, &*physics_);
    eventQueue_.RegisterEventHandler(ZarchEvent::ControlsStateEvent, &*physics_);
    eventQueue_.RegisterEventHandler(ZarchEvent::LanderMovedEvent, &*video_);
    
    
    threadingFactory_         = threadingFactory;
    simulationCouplingBuffer_ = shared_ptr<ThreadCouplingBuffer>(
                                    new ThreadCouplingBuffer(*threadingFactory_));
    simulation_               = shared_ptr<Simulation>(
                                    new Simulation(simulationCouplingBuffer_, 0));
    presentation_             = shared_ptr<Presentation>(
                                    new Presentation(simulationCouplingBuffer_, 1));
}

Zarch::~Zarch() {
}

void Zarch::Execute(const FrameTimeProcess::FrameTimeInfo &timeInfo,
                    const ControlsState &controlsState) {
    static_cast<VariantEvent &>(eventQueue_.ScheduleEvent(ZarchEvent::FrameTimeEvent))
        .Reset(timeInfo.timeSinceLastFrame);
    static_cast<ControlsStateEvent &>(eventQueue_.ScheduleEvent(ZarchEvent::ControlsStateEvent))
        .Reset(controlsState);
    
    physics_->ExecuteProcesses();
    eventQueue_.ProcessEvents();
    video_->ExecuteProcesses();
    
    gameLogic_->ExecuteProcesses();
    
    
    presentation_->PrepareFrame();
}

void Zarch::SetViewPort(int width, int height) {
    projection_->SetViewPort((float)width, (float)height);
    Log().Stream() << "viewport set" << ", size=(" << (int)width << "," << (int)height << ")"
                   << endl;
    
    presentation_->SetViewPort(width, height);
}

void Zarch::RenderFrame() {
    projection_->Render(0);
    
    presentation_->RenderFrame();
}

}    // Namespace Zarch.
}    // Namespace kxm.
