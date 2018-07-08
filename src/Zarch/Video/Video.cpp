#include <kxm/Zarch/Video/Video.h>

#include <kxm/Core/logging.h>
#include <kxm/Core/NumberTools.h>
#include <kxm/Vectoid/PerspectiveProjection.h>
#include <kxm/Vectoid/Camera.h>
#include <kxm/Vectoid/CoordSys.h>
#include <kxm/Vectoid/Geode.h>
#include <kxm/Vectoid/Particles.h>
#include <kxm/Vectoid/ParticlesRenderer.h>
#include <kxm/Vectoid/AgeColoredParticles.h>
#include <kxm/Vectoid/Transform.h>
#include <kxm/Vectoid/Glyphs.h>
#include <kxm/Vectoid/TextConsole.h>
#include <kxm/Game/EventLoop.h>
#include <kxm/Game/Actions.h>
#include <kxm/Zarch/ControlsState.h>
#include <kxm/Zarch/MapParameters.h>
#include <kxm/Zarch/Terrain.h>
#include <kxm/Zarch/EventTools.h>
#include <kxm/Zarch/Video/RenderTargetInterface.h>
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
#include <kxm/Zarch/Events/PlayerStatsEvent.h>

using namespace std;
using namespace std::chrono;
using namespace kxm::Core;
using namespace kxm::Vectoid;
using namespace kxm::Game;

namespace kxm {
namespace Zarch {
namespace Video {

Video::Video(const shared_ptr<EventLoop<ZarchEvent, EventHandlerCore>> &eventLoop,
             const shared_ptr<RenderTargetInterface> &renderTarget)
        : data_(new Data()),
          eventLoop_(eventLoop),
          actions_(new Actions()),
          landers_(actions_, data_),
          shots_(actions_, data_),
          saucers_(actions_, data_),
          lastFrameTime_(steady_clock::now()),
          thruster_(false),
          trigger_(false),
          fpsFrameCounter_(0),
          fpsTimeS_(0.0f) {
    eventLoop_->RegisterHandler(ActorCreationEvent::type,    this);
    eventLoop_->RegisterHandler(ActorTerminationEvent::type, this);
    eventLoop_->RegisterHandler(ControlsEvent::type,         this);
    eventLoop_->RegisterHandler(MoveEvent::type,             this);
    eventLoop_->RegisterHandler(VelocityEvent::type,         this);
    eventLoop_->RegisterHandler(TriggerEvent::type,          this);
    eventLoop_->RegisterHandler(PlayerStatsEvent::type,      this);
    
    data_->renderTarget  = renderTarget;
    data_->mapParameters = make_shared<MapParameters>();
    data_->terrain       = make_shared<Terrain>(data_->mapParameters);
    
    // Install scene graph...
    data_->projection = renderTarget->NewPerspectiveProjection();
    data_->projection->SetWindowSize(11.0f);
    data_->projection->SetViewingDepth(11.0f);
    data_->projection->SetEyepointDistance(11.0f);
    data_->camera = renderTarget->NewCamera();
    data_->projection->AddChild(data_->camera);
    
    data_->terrainRenderer = renderTarget->NewTerrainRenderer(data_->terrain, data_->mapParameters);
    data_->camera->AddChild(make_shared<Geode>(data_->terrainRenderer));
    
    data_->shotParticles = make_shared<Particles>();
    data_->camera->AddChild(make_shared<Geode>(renderTarget->NewParticlesRenderer(data_->shotParticles)));
    data_->thrusterParticles = make_shared<Particles>();
    data_->camera->AddChild(make_shared<Geode>(renderTarget->NewAgeColoredParticles(data_->thrusterParticles)));
    shared_ptr<Particles> starFieldParticles(new Particles());
    data_->camera->AddChild(make_shared<Geode>(renderTarget->NewParticlesRenderer(starFieldParticles)));
    
    data_->statsConsole = renderTarget->NewTextConsole(20, 4, .2f, .2f, renderTarget->NewGlyphs());
    data_->statsConsoleCoordSys = renderTarget->NewCoordSys();
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

void Video::Handle(const PlayerStatsEvent &event) {
    if (!data_->focusLander.IsNone() && (data_->focusLander == event.actor)) {
        char text[80];
        PlayerStatsEvent::Stat stat;
        for (int i = 0; i < event.StatCount(); ++i) {
            event.GetStat(i, &stat);
            switch (stat.type) {
                case PlayerStatsEvent::FuelStat:
                    NumberTools::Clamp(&stat.value, 0, 99999999);
                    std::sprintf(text, "%08d", stat.value);
                    data_->statsConsole->WriteAt(12, 1, text);
                    break;
                default:
                    break;
            }
        }
    }
}

void Video::Handle(const TriggerEvent &event) {
    if (event.trigger == TriggerEvent::FrameRenderedTrigger) {
        Data &data = *data_;
        auto now = steady_clock::now();
        int milliSeconds = (int)duration_cast<milliseconds>(now - lastFrameTime_).count();
        lastFrameTime_ = now;
        data.frameDeltaTimeS = (float)milliSeconds / 1000.0f;
        
        Vector observerPosition;
        data.terrainRenderer->GetObserverPosition(&observerPosition);
        
        for (Particles::ParticleInfo &particle : data.shotParticles->Iterate()) {
            data.mapParameters->CorrectForObserver(&particle.position, observerPosition);
        }
        
        // Move and age thruster particles...
        auto iter = data.thrusterParticles->Iterate().begin();
        while (!iter.AtEnd()) {
            Particles::ParticleInfo *particle = &*iter;
            particle->velocity.y += data.frameDeltaTimeS * -data.mapParameters->gravity;
            particle->position   += data.frameDeltaTimeS * particle->velocity;
            data.mapParameters->xRange.ClampModulo(&particle->position.x);
            data.mapParameters->zRange.ClampModulo(&particle->position.z);
            data.mapParameters->CorrectForObserver(&particle->position, observerPosition);
            particle->age        += data.frameDeltaTimeS;
            if (particle->age >= data.mapParameters->maxThrusterParticleAge) {
                data.thrusterParticles->Remove(iter.ItemId());
            }
            
            ++iter;
        }
        
        actions_->Execute();
        
        ++fpsFrameCounter_;
        fpsTimeS_ += data.frameDeltaTimeS;
        if (fpsTimeS_ >= 2.0f) {
            float fps = (float)fpsFrameCounter_ / fpsTimeS_;
            NumberTools::Clamp(&fps, 0.0f, 500.0f);
            char text[80];
            std::sprintf(text, "%03d", (int)(fps + .5f));
            data.statsConsole->WriteAt(0, 2, text);
            fpsFrameCounter_ = 0;
            fpsTimeS_        = 0.0f;
        }
        
        data.projection->Render(0);
        eventLoop_->Post(TriggerEvent(TriggerEvent::FrameRenderedTrigger, 0.0f));
    }
}

}    // Namespace Video.
}    // Namespace Zarch.
}    // Namespace kxm.

