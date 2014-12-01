//
//  NewVideo.cpp
//  kxm
//
//  Created by Kai Hergenröther on 4/28/13.
//
//


#include <kxm/Zarch/Video/Video.h>

#include <kxm/Core/logging.h>
#include <kxm/Vectoid/PerspectiveProjection.h>
#include <kxm/Vectoid/Camera.h>
#include <kxm/Vectoid/CoordSys.h>
#include <kxm/Vectoid/Geode.h>
#include <kxm/Vectoid/Particles.h>
#include <kxm/Vectoid/AgeColoredParticles.h>
#include <kxm/Vectoid/ParticlesRenderer.h>
#include <kxm/Vectoid/Transform.h>
#include <kxm/Game/Processes.h>
#include <kxm/Zarch/Video/CameraProcess.h>
#include <kxm/Zarch/Video/StarFieldProcess.h>
#include <kxm/Zarch/Video/ThrusterParticlesProcess.h>
#include <kxm/Zarch/Video/TerrainRenderer.h>
#include <kxm/Zarch/LanderGeometry.h>
#include <kxm/Zarch/MapParameters.h>
#include <kxm/Zarch/Terrain.h>
#include <kxm/Zarch/Events/ZarchEvent.h>
#include <kxm/Zarch/Events/FrameTimeEvent.h>
#include <kxm/Zarch/Events/LanderMoveEvent.h>
#include <kxm/Zarch/Events/LanderVelocityEvent.h>
#include <kxm/Zarch/Events/LanderThrusterEvent.h>


using namespace std;
using namespace kxm::Vectoid;
using namespace kxm::Game;


namespace kxm {
namespace Zarch {

Video::Video(shared_ptr<Processes<ZarchProcess::ProcessType>> processes)
        : processes_(processes) {
    data_ = shared_ptr<Data>(new Data());
    data_->mapParameters = shared_ptr<MapParameters>(new MapParameters());
    data_->terrain       = shared_ptr<Terrain>(new Terrain(data_->mapParameters));
    
    // Install scene graph...
    data_->projection = shared_ptr<PerspectiveProjection>(new PerspectiveProjection());
    data_->projection->SetWindowSize(11.0f);
    data_->projection->SetViewingDepth(11.0f);
    data_->projection->SetEyepointDistance(11.0f);
    data_->camera = shared_ptr<Camera>(new Camera());
    data_->projection->AddChild(data_->camera);
    data_->landerCoordSys = shared_ptr<CoordSys>(new CoordSys());
    data_->camera->AddChild(data_->landerCoordSys);
    shared_ptr<LanderGeometry> landerGeometry(new LanderGeometry());
    data_->landerCoordSys->AddChild(shared_ptr<Geode>(new Geode(landerGeometry)));
    data_->terrainRenderer = shared_ptr<TerrainRenderer>(new TerrainRenderer(data_->terrain,
                                                                             data_->mapParameters));
    data_->camera->AddChild(shared_ptr<Geode>(new Geode(data_->terrainRenderer)));
    
    shared_ptr<Particles> thrusterParticles(new Particles()),
                          shotsParticles(new Particles()),
                          starFieldParticles(new Particles());
    data_->camera->AddChild(shared_ptr<Geode>(new Geode(shared_ptr<AgeColoredParticles>(
        new AgeColoredParticles(thrusterParticles)))));
    data_->camera->AddChild(shared_ptr<Geode>(new Geode(shared_ptr<ParticlesRenderer>(
        new ParticlesRenderer(shotsParticles)))));
    data_->camera->AddChild(shared_ptr<Geode>(new Geode(shared_ptr<ParticlesRenderer>(
        new ParticlesRenderer(starFieldParticles)))));
    
    processes_->AddProcess(shared_ptr<Process>(new CameraProcess(data_)));
    processes_->AddProcess(shared_ptr<Process>(new StarFieldProcess(data_, starFieldParticles)));
    processes_->AddProcess(shared_ptr<Process>(new ThrusterParticlesProcess(data_,
                                                                            thrusterParticles)));
}

void Video::SetViewPort(int width, int height) {
    data_->projection->SetViewPort((float)width, (float)height);
}

void Video::RenderFrame() {
    data_->projection->Render(0);
}

void Video::HandleEvent(const Game::Event &event) {
    static_cast<const Zarch::ZarchEvent &>(event).DispatchToVideo(this);
}

void Video::HandleFrameTimeEvent(const FrameTimeEvent &event) {
    data_->frameDeltaTimeS = event.timeS;
}

void Video::HandleLanderMoveEvent(const LanderMoveEvent &event) {
    data_->landerCoordSys->SetTransform(event.newLanderTransform);
    
    Vector landerPosition = data_->landerCoordSys->Position();
    data_->terrainRenderer->SetObserverPosition(landerPosition.x, landerPosition.z);
}

void Video::HandleLanderVelocityEvent(const LanderVelocityEvent &event) {
    data_->landerVelocity = event.velocity;
}

void Video::HandleLanderThrusterEvent(const LanderThrusterEvent &event) {
    data_->landerThrusterEnabled = event.thrusterEnabled;
}

void Video::HandleEvent(const Game::OldEvent &event) {
    return;
    switch (static_cast<const OldZarchEvent &>(event).Type()) {
        case OldZarchEvent::FrameTimeEvent:
            data_->frameDeltaTimeS = static_cast<const OldEvent<Variant> &>(event).Data().AsFloat();
            break;
            
        case OldZarchEvent::LanderMoveEvent:
            HandleLanderMovedEvent(static_cast<const OldEvent<Transform> &>(event));
            break;
            
        case OldZarchEvent::LanderVelocityEvent:
            data_->landerVelocity = static_cast<const OldEvent<Vector> &>(event).Data();
            break;
        
        case OldZarchEvent::LanderThrusterEvent:
            data_->landerThrusterEnabled = static_cast<const OldEvent<Variant> &>(event)
                                               .Data().AsBool();
            break;
        
        default:
            break;
    }
}

void Video::HandleLanderMovedEvent(const OldEvent<Transform> &event) {
    data_->landerCoordSys->SetTransform(event.Data());
    
    Vector landerPosition = data_->landerCoordSys->Position();
    data_->terrainRenderer->SetObserverPosition(landerPosition.x, landerPosition.z);
}

}    // Namespace Zarch.
}    // Namespace kxm.

