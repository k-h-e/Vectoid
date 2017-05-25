#include <kxm/Zarch/Video/Video.h>

#include <kxm/Core/logging.h>
#include <kxm/Vectoid/PerspectiveProjection.h>
#include <kxm/Vectoid/Camera.h>
#include <kxm/Vectoid/CoordSys.h>
#include <kxm/Vectoid/Geode.h>
#include <kxm/Vectoid/Particles.h>
#include <kxm/Vectoid/ParticlesRenderer.h>
#include <kxm/Vectoid/Transform.h>
#include <kxm/Vectoid/Glyphs.h>
#include <kxm/Vectoid/TextConsole.h>
#include <kxm/Game/EventLoop.h>
#include <kxm/Game/Actions.h>
#include <kxm/Zarch/ControlsState.h>
#include <kxm/Zarch/LanderGeometry.h>
#include <kxm/Zarch/MapParameters.h>
#include <kxm/Zarch/Terrain.h>
#include <kxm/Zarch/EventTools.h>
#include <kxm/Zarch/Video/Shot.h>
#include <kxm/Zarch/Video/Saucer.h>
#include <kxm/Zarch/Video/StarField.h>
#include <kxm/Zarch/Video/TerrainRenderer.h>
#include <kxm/Zarch/Events/ZarchEvent.h>
#include <kxm/Zarch/Events/ActorCreationEvent.h>
#include <kxm/Zarch/Events/ActorTerminationEvent.h>
#include <kxm/Zarch/Events/ControlsEvent.h>
#include <kxm/Zarch/Events/ControlsRequestEvent.h>
#include <kxm/Zarch/Events/MoveEvent.h>
#include <kxm/Zarch/Events/VelocityEvent.h>
#include <kxm/Zarch/Events/TriggerEvent.h>

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
          saucers_(actions_),
          lastFrameTime_(steady_clock::now()),
          thruster_(false),
          trigger_(false) {
    eventLoop_->RegisterHandler(ActorCreationEvent::type,    this);
    eventLoop_->RegisterHandler(ActorTerminationEvent::type, this);
    eventLoop_->RegisterHandler(ControlsEvent::type,         this);
    eventLoop_->RegisterHandler(MoveEvent::type,             this);
    eventLoop_->RegisterHandler(VelocityEvent::type,         this);
    eventLoop_->RegisterHandler(TriggerEvent::type,          this);
    
    data_ = make_shared<Data>();
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
    
    data_->statsConsole = make_shared<TextConsole>(20, 4, .2f, .2f, make_shared<Glyphs>());
    data_->statsConsoleCoordSys = make_shared<CoordSys>();
    Transform transform(YAxis, -40.0f);
    transform.Prepend(Transform(ZAxis, -12.0f));
    transform.Prepend(Transform(XAxis,  30.0f));
    data_->statsConsoleCoordSys->SetTransform(transform);
    data_->statsConsoleCoordSys->AddChild(make_shared<Geode>(data_->statsConsole));
    data_->camera->AddAsLastChild(data_->statsConsoleCoordSys);
    data_->statsConsole->WriteLine("      SCORE 00000000");
    data_->statsConsole->WriteLine("FPS   FUEL  00000000");
    data_->statsConsole->WriteLine("000   LIVES      000");
    data_->statsConsole->WriteLine("");
    
    
    starField_ = unique_ptr<StarField>(new StarField(data_, starFieldParticles));
    actions_->Register(starField_.get());
}

Video::~Video() {
    // Nop.
}

void Video::SetViewPort(int width, int height) {
    data_->projection->SetViewPort((float)width, (float)height);
    
    data_->statsConsolePosition =   data_->projection->TransformViewPortCoordinates(width, 0)
                                  + Vector(-1.5f, 0.0f, -1.5f);
}

void Video::PrepareFrame(const ControlsState &controlsState) {
    if (!data_->focusLander.IsNone()) {
        ControlsRequestEvent event(data_->focusLander);
        event.AddControl(Control(Axis1Control, controlsState.orientation.x));
        event.AddControl(Control(Axis2Control, controlsState.orientation.y));
        if (controlsState.thruster != thruster_) {
            event.AddControl(Control(ThrusterControl, controlsState.thruster ? 1.0f : 0.0f));
            thruster_ = controlsState.thruster;
        }
        if (controlsState.trigger != trigger_) {
            event.AddControl(Control(TriggerControl, controlsState.trigger ? 1.0f : 0.0f));
            trigger_ = controlsState.trigger;
        }
        eventLoop_->Post(event);
    }
}

void Video::Handle(const ActorCreationEvent &event) {
    Actor *actor = nullptr;
    int   storageId;
    switch (event.actorType) {
        case LanderActor:
            actor = landers_.Get(&storageId);
            break;
        case ShotActor:
            actor = shots_.Get(&storageId);
            break;
        case SaucerActor:
            actor = saucers_.Get(&storageId);
            break;
        default:
            break;
    }
    
    if (actor) {
        const ActorCreationEvent *eventToUse = &event;
        ActorCreationEvent cookedEvent;
        if (!event.launchingActor.IsNone()) {
            ActorInfo<Actor> *info = actorMap_.Get(event.launchingActor);
            assert(info);
            Transform launchingActorTransform;
            info->Actor()->GetTransform(&launchingActorTransform);
            Vector launchingActorVelocity;
            info->Actor()->GetVelocity(&launchingActorVelocity);
            
            cookedEvent = event;
            EventTools::ResolveInitialTransformAndVelocity(&cookedEvent, launchingActorTransform,
                                                           launchingActorVelocity);
            eventToUse = &cookedEvent;
        }

        actor->SetData(data_);
        actor->Handle(*eventToUse);
        actorMap_.Register(eventToUse->actor, ActorInfo<Actor>(eventToUse->actorType, storageId, actor));
    }
}

void Video::Handle(const ActorTerminationEvent &event) {
    ActorInfo<Actor> *info = actorMap_.Get(event.actor);
    if (info) {
        info->Actor()->Handle(event);
        
        switch (info->Type()) {
            case LanderActor:
                landers_.Put(info->StorageId());
                break;
            case ShotActor:
                shots_.Put(info->StorageId());
                break;
            case SaucerActor:
                saucers_.Put(info->StorageId());
                break;
            default:
                assert(false);
                break;
        }
        // Don't use info->actor() below.
        
        actorMap_.Unregister(event.actor);
    }
}

void Video::Handle(const ControlsEvent &event) {
    ActorInfo<Actor> *info = actorMap_.Get(event.actor);
    if (info && (info->Type() == LanderActor)) {
        info->Actor()->Handle(event);
    }
}

void Video::Handle(const MoveEvent &event) {
    ActorInfo<Actor> *info = actorMap_.Get(event.actor);
    if (info) {
        info->Actor()->Handle(event);
    }
}

void Video::Handle(const VelocityEvent &event) {
    ActorInfo<Actor> *info = actorMap_.Get(event.actor);
    if (info && (info->Type() == LanderActor)) {
        info->Actor()->Handle(event);
    }
}

void Video::Handle(const TriggerEvent &event) {
    if (event.trigger == TriggerEvent::FrameRenderedTrigger) {
        auto now = steady_clock::now();
        int milliSeconds = (int)duration_cast<milliseconds>(now - lastFrameTime_).count();
        lastFrameTime_ = now;
        data_->frameDeltaTimeS = (float)milliSeconds / 1000.0f;
        
        actions_->Execute();
        
        Vector observerPosition;
        data_->terrainRenderer->GetObserverPosition(&observerPosition);
        auto iter = data_->shotParticles->GetIterator();
        while (Particles::ParticleInfo *particle = iter.Next()) {
            data_->mapParameters->CorrectForObserver(&particle->position, observerPosition);
        }
        
        data_->projection->Render(0);
        eventLoop_->Post(TriggerEvent(TriggerEvent::FrameRenderedTrigger, 0.0f));
    }
}

}    // Namespace Video.
}    // Namespace Zarch.
}    // Namespace kxm.

