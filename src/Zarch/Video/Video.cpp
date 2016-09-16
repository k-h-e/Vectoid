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
#include <Game/Actions.h>
#include <Zarch/LanderGeometry.h>
#include <Zarch/MapParameters.h>
#include <Zarch/Terrain.h>
#include <Zarch/Video/Shot.h>
#include <Zarch/Video/StarField.h>
#include <Zarch/Video/TerrainRenderer.h>
#include <Zarch/Events/ZarchEvent.h>
#include <Zarch/Events/ActorCreationEvent.h>
#include <Zarch/Events/ActorTerminationEvent.h>
#include <Zarch/Events/FrameGeneratedEvent.h>
#include <Zarch/Events/MoveEvent.h>
#include <Zarch/Events/VelocityEvent.h>
#include <Zarch/Events/AccelerationEvent.h>
#include <Zarch/Events/ControlsEvent.h>

using namespace std;
using namespace std::chrono;
using namespace kxm::Vectoid;
using namespace kxm::Game;

namespace kxm {
namespace Zarch {
namespace Video {

Video::Video(shared_ptr<EventLoop<ZarchEvent, EventHandlerCore>> eventLoop)
        : eventLoop_(eventLoop),
          actions_(new Actions()),
          landers_(actions_),
          shots_(actions_),
          lastFrameTime_(steady_clock::now()) {
    eventLoop_->RegisterHandler(ActorCreationEvent::type,    this);
    eventLoop_->RegisterHandler(ActorTerminationEvent::type, this);
    eventLoop_->RegisterHandler(FrameGeneratedEvent::type,   this);
    eventLoop_->RegisterHandler(MoveEvent::type,             this);
    eventLoop_->RegisterHandler(VelocityEvent::type,         this);
    eventLoop_->RegisterHandler(AccelerationEvent::type,     this);
    
    data_ = shared_ptr<Data>(new Data());
    data_->mapParameters = make_shared<MapParameters>();
    data_->terrain       = make_shared<Terrain>(data_->mapParameters);
    
    // Install scene graph...
    data_->projection = make_shared<PerspectiveProjection>();
    data_->projection->SetWindowSize(11.0f);
    data_->projection->SetViewingDepth(11.0f);
    data_->projection->SetEyepointDistance(11.0f);
    data_->camera = make_shared<Camera>();
    data_->projection->AddChild(data_->camera);
    
    data_->terrainRenderer = make_shared<TerrainRenderer>(data_->terrain, data_->mapParameters);
    data_->camera->AddChild(make_shared<Geode>(data_->terrainRenderer));
    
    shared_ptr<Particles> shotParticles(new Particles()),
                          starFieldParticles(new Particles());
    data_->shotParticles = shotParticles;
    data_->camera->AddChild(make_shared<Geode>(make_shared<ParticlesRenderer>(shotParticles)));
    data_->camera->AddChild(make_shared<Geode>(make_shared<ParticlesRenderer>(starFieldParticles)));
    
    starField_ = unique_ptr<StarField>(new StarField(data_, starFieldParticles));
    actions_->Register(starField_.get());
}

Video::~Video() {
    // Nop.
}

void Video::SetViewPort(int width, int height) {
    data_->projection->SetViewPort((float)width, (float)height);
}

void Video::PrepareFrame(const ControlsState &controlsState) {
    if (!landerName_.IsNone()) {
        eventLoop_->Post(ControlsEvent(landerName_, controlsState));
    }
}

void Video::Handle(const ActorCreationEvent &event) {
    int              storageId;
    EventHandlerCore *newActor = nullptr;
    switch (event.actorType) {
        case LanderActor:
            newActor = landers_.Get(&storageId);
            static_cast<Lander *>(newActor)->Reset(landerName_.IsNone(), data_);
            if (landerName_.IsNone()) {
                landerName_ = event.actor;
            }
            break;
            
        case ShotActor:
            newActor = shots_.Get(&storageId);
            static_cast<Shot *>(newActor)->Reset(data_);
            break;
            
        default:
            break;
    }
    
    if (newActor) {
        newActor->Handle(event);
        actorMap_.Register(event.actor, ActorInfo<EventHandlerCore>(event.actorType, storageId, newActor));
    }
}

void Video::Handle(const ActorTerminationEvent &event) {
    ActorInfo<EventHandlerCore> *info = actorMap_.Get(event.actor);
    if (info) {
        info->actor()->Handle(event);
        
        switch (info->type()) {
            case LanderActor:
                landers_.Put(info->storageId());
                if (landerName_ == event.actor) {
                    landerName_ = ActorName();
                }
                break;
            case ShotActor:
                shots_.Put(info->storageId());
                break;
            default:
                assert(false);
                break;
        }
        // Don't use info->actor() below.
        
        actorMap_.Unregister(event.actor);
    }
}

void Video::Handle(const MoveEvent &event) {
    ActorInfo<EventHandlerCore> *info = actorMap_.Get(event.actor);
    if (info) {
        info->actor()->Handle(event);
    }
}

void Video::Handle(const VelocityEvent &event) {
    ActorInfo<EventHandlerCore> *info = actorMap_.Get(event.actor);
    if (info) {
        info->actor()->Handle(event);
    }
}

void Video::Handle(const AccelerationEvent &event) {
    ActorInfo<EventHandlerCore> *info = actorMap_.Get(event.actor);
    if (info) {
        info->actor()->Handle(event);
    }
}

void Video::Handle(const FrameGeneratedEvent &event) {
    auto now = steady_clock::now();
    int milliSeconds = (int)duration_cast<milliseconds>(now - lastFrameTime_).count();
    lastFrameTime_ = now;
    data_->frameDeltaTimeS = (float)milliSeconds / 1000.0f;
    
    actions_->Execute();
    
    float observerX, observerZ;
    data_->terrainRenderer->GetObserverPosition(&observerX, &observerZ);
    auto iter = data_->shotParticles->GetIterator();
    while (Particles::ParticleInfo *particle = iter.Next()) {
        data_->mapParameters->xRange.ExpandModuloForObserver(observerX, &particle->position.x);
        data_->mapParameters->zRange.ExpandModuloForObserver(observerZ, &particle->position.z);
    }
    
    data_->projection->Render(0);
    eventLoop_->Post(FrameGeneratedEvent());
}

}    // Namespace Video.
}    // Namespace Zarch.
}    // Namespace kxm.

