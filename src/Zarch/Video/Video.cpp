#include <Zarch/Video/Video.h>

#include <kxm/Core/logging.h>
#include <Vectoid/PerspectiveProjection.h>
#include <Vectoid/Camera.h>
#include <Vectoid/CoordSys.h>
#include <Vectoid/Geode.h>
#include <Vectoid/Particles.h>
#include <Vectoid/ParticlesRenderer.h>
#include <Vectoid/Transform.h>
#include <Game/EventLoop.h>
#include <Zarch/Video/StarFieldProcess.h>
#include <Zarch/Video/TerrainRenderer.h>
#include <Zarch/LanderGeometry.h>
#include <Zarch/MapParameters.h>
#include <Zarch/Terrain.h>
#include <Zarch/Events/ZarchEvent.h>
#include <Zarch/Events/ActorCreatedEvent.h>
#include <Zarch/Events/FrameGeneratedEvent.h>
#include <Zarch/Events/MoveEvent.h>
#include <Zarch/Events/LanderVelocityEvent.h>
#include <Zarch/Events/LanderThrusterEvent.h>

using namespace std;
using namespace std::chrono;
using namespace kxm::Vectoid;
using namespace kxm::Game;

namespace kxm {
namespace Zarch {
namespace Video {

Video::Video(shared_ptr<EventLoop<ZarchEvent, EventHandlerCore>> eventLoop)
        : eventLoop_(eventLoop),
          landerInUse_(false),
          lastFrameTime_(steady_clock::now()) {
    eventLoop_->RegisterHandler(ActorCreatedEvent::type,   this);
    eventLoop_->RegisterHandler(FrameGeneratedEvent::type, this);
    eventLoop_->RegisterHandler(MoveEvent::type,           this);
    eventLoop_->RegisterHandler(LanderVelocityEvent::type, this);
    eventLoop_->RegisterHandler(LanderThrusterEvent::type, this);
    
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
    
    data_->terrainRenderer = shared_ptr<TerrainRenderer>(new TerrainRenderer(data_->terrain,
                                                                             data_->mapParameters));
    data_->camera->AddChild(shared_ptr<Geode>(new Geode(data_->terrainRenderer)));
    
    shared_ptr<Particles> shotsParticles(new Particles()),
                          starFieldParticles(new Particles());
    data_->camera->AddChild(shared_ptr<Geode>(new Geode(shared_ptr<ParticlesRenderer>(
        new ParticlesRenderer(shotsParticles)))));
    data_->camera->AddChild(shared_ptr<Geode>(new Geode(shared_ptr<ParticlesRenderer>(
        new ParticlesRenderer(starFieldParticles)))));
    
    
    lander_ = unique_ptr<Lander>(new Lander(data_));
    starFieldProcess_ = unique_ptr<StarFieldProcess>(new StarFieldProcess(data_, starFieldParticles));
}

Video::~Video() {
    // Nop.
}

void Video::SetViewPort(int width, int height) {
    data_->projection->SetViewPort((float)width, (float)height);
}

void Video::HandleProcessFinished(Game::ProcessInterface *process) {
    // Nop.
}

void Video::Handle(const ActorCreatedEvent &event) {
    switch (event.actorType) {
        case LanderActor:
            assert(!landerInUse_);
            actors_.Register(event.actor, lander_.get());
            lander_->AttachToCamera(data_->camera);
            landerInUse_ = true;
            break;
            
        default:
            break;
    }
}

void Video::Handle(const FrameGeneratedEvent &event) {
    auto now = steady_clock::now();
    int milliSeconds = (int)duration_cast<milliseconds>(now - lastFrameTime_).count();
    lastFrameTime_ = now;
    data_->frameDeltaTimeS = (float)milliSeconds / 1000.0f;
    
    if (landerInUse_) {
        lander_->Execute();
        
        Vector landerPosition;
        lander_->GetPosition(&landerPosition);
        
        Vector cameraPosition = landerPosition;
        if (cameraPosition.y < data_->mapParameters->cameraMinHeight) {
            cameraPosition.y = data_->mapParameters->cameraMinHeight;
        }
        data_->camera->SetPosition(Vector(cameraPosition.x, cameraPosition.y, cameraPosition.z + 5.0f));
    
        data_->terrainRenderer->SetObserverPosition(landerPosition.x, landerPosition.z);
    }
    
    starFieldProcess_->Execute();
    
    data_->projection->Render(0);
    eventLoop_->Post(FrameGeneratedEvent());
}

void Video::Handle(const MoveEvent &event) {
    EventHandlerCore *actor = actors_.Get(event.actor);
    if (actor) {
        actor->Handle(event);
    }
}

void Video::Handle(const LanderVelocityEvent &event) {
    data_->landerVelocity = event.velocity;
}

void Video::Handle(const LanderThrusterEvent &event) {
    data_->landerThrusterEnabled = event.thrusterEnabled;
}

}    // Namespace Video.
}    // Namespace Zarch.
}    // Namespace kxm.

