#include <kxm/Zarch/Physics/Physics.h>

#include <kxm/Core/logging.h>
#include <kxm/Game/EventLoop.h>
#include <kxm/Zarch/Physics/Lander.h>
#include <kxm/Zarch/MapParameters.h>
#include <kxm/Zarch/Terrain.h>
#include <kxm/Zarch/ControlsState.h>
#include <kxm/Zarch/EventTools.h>
#include <kxm/Zarch/Events/ZarchEvent.h>
#include <kxm/Zarch/Events/ActorCreationEvent.h>
#include <kxm/Zarch/Events/ControlsEvent.h>
#include <kxm/Zarch/Events/ActorTerminationEvent.h>
#include <kxm/Zarch/Events/AccelerationEvent.h>
#include <kxm/Zarch/Events/PhysicsOverrideEvent.h>
#include <kxm/Zarch/Events/TriggerEvent.h>
#include <kxm/Zarch/Physics/Data.h>
#include <kxm/Zarch/Physics/Shot.h>
#include <kxm/Zarch/Physics/Saucer.h>

using namespace std;
using namespace kxm::Core;
using namespace kxm::Game;
using namespace kxm::Vectoid;

namespace kxm {
namespace Zarch {
namespace Physics {

Physics::Physics(shared_ptr<EventLoop<ZarchEvent, EventHandlerCore>> eventLoop,
                 TriggerEvent::Trigger anInTrigger, TriggerEvent::Trigger anOutTrigger)
        : actions_(new Actions()),
          landers_(actions_),
          shots_(actions_),
          saucers_(actions_),
          inTrigger_(anInTrigger),
          outTrigger_(anOutTrigger) {
    data_ = make_shared<Data>();
    data_->mapParameters = make_shared<MapParameters>();
    data_->terrain       = make_shared<Terrain>(data_->mapParameters);
    data_->eventLoop     = eventLoop;
    
    data_->eventLoop->RegisterHandler(ActorCreationEvent::type,    this);
    data_->eventLoop->RegisterHandler(ActorTerminationEvent::type, this);
    data_->eventLoop->RegisterHandler(ControlsEvent::type,         this);
    data_->eventLoop->RegisterHandler(PhysicsOverrideEvent::type,  this);
    data_->eventLoop->RegisterHandler(AccelerationEvent::type,     this);
    data_->eventLoop->RegisterHandler(TriggerEvent::type,          this);
}

Physics::~Physics() {
    // Nop.
}

void Physics::Handle(const ActorCreationEvent &event) {
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
            info->actor()->GetTransform(&launchingActorTransform);
            Vector launchingActorVelocity;
            info->actor()->GetVelocity(&launchingActorVelocity);
            
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

void Physics::Handle(const ActorTerminationEvent &event) {
    ActorInfo<Actor> *info = actorMap_.Get(event.actor);
    if (info) {
        switch (info->type()) {
            case LanderActor:
                landers_.Put(info->storageId());
                break;
            case ShotActor:
                shots_.Put(info->storageId());
                break;
            case SaucerActor:
                saucers_.Put(info->storageId());
                break;
            default:
                assert(false);
                break;
        }
        // Don't use info->actor() below.
        
        actorMap_.Unregister(event.actor);
    }
}

void Physics::Handle(const ControlsEvent &event) {
    ActorInfo<Actor> *info = actorMap_.Get(event.actor);
    if (info) {
        info->actor()->Handle(event);
    }
}

void Physics::Handle(const PhysicsOverrideEvent &event) {
    ActorInfo<Actor> *info = actorMap_.Get(event.actor);
    if (info) {
        info->actor()->Handle(event);
    }
}

void Physics::Handle(const AccelerationEvent &event) {
    ActorInfo<Actor> *info = actorMap_.Get(event.actor);
    if (info && (   (info->type() == LanderActor)
                 || (info->type() == SaucerActor))) {
        info->actor()->Handle(event);
    }
}

void Physics::Handle(const TriggerEvent &event) {
    if ((inTrigger_ != TriggerEvent::NoTrigger) && (event.trigger == inTrigger_)) {
        data_->updateDeltaTimeS = event.deltaTime_s;
        actions_->Execute();
        if (outTrigger_ != TriggerEvent::NoTrigger) {
            data_->eventLoop->Post(TriggerEvent(outTrigger_, event.deltaTime_s));
        }
    }
}

}    // Namespace Physics.
}    // Namespace Zarch.
}    // Namespace kxm.
