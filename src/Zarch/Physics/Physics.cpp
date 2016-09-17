#include <kxm/Zarch/Physics/Physics.h>

#include <kxm/Core/logging.h>
#include <kxm/Game/EventLoop.h>
#include <kxm/Zarch/Physics/Lander.h>
#include <kxm/Zarch/MapParameters.h>
#include <kxm/Zarch/Terrain.h>
#include <kxm/Zarch/ControlsState.h>
#include <kxm/Zarch/Events/ZarchEvent.h>
#include <kxm/Zarch/Events/TimeEvent.h>
#include <kxm/Zarch/Events/UpdatePhysicsEvent.h>
#include <kxm/Zarch/Events/ActorCreationEvent.h>
#include <kxm/Zarch/Events/ActorTerminationEvent.h>
#include <kxm/Zarch/Events/PhysicsUpdatedEvent.h>
#include <kxm/Zarch/Events/PhysicsOverrideEvent.h>
#include <kxm/Zarch/Events/AccelerationEvent.h>
#include <kxm/Zarch/Physics/Data.h>
#include <kxm/Zarch/Physics/Shot.h>

using namespace std;
using namespace std::chrono;
using namespace kxm::Core;
using namespace kxm::Game;
using namespace kxm::Vectoid;

namespace kxm {
namespace Zarch {
namespace Physics {

Physics::Physics(shared_ptr<EventLoop<ZarchEvent, EventHandlerCore>> eventLoop, bool emitTimeEvents)
        : actions_(new Actions()),
          landers_(actions_),
          shots_(actions_),
          lastUpdateTime_(steady_clock::now()),
          emitTimeEvents_(emitTimeEvents) {
    data_ = shared_ptr<Data>(new Data());
    data_->mapParameters = shared_ptr<MapParameters>(new MapParameters());
    data_->terrain       = shared_ptr<Terrain>(new Terrain(data_->mapParameters));
    data_->eventLoop     = eventLoop;
    
    data_->eventLoop->RegisterHandler(ActorCreationEvent::type,    this);
    data_->eventLoop->RegisterHandler(ActorTerminationEvent::type, this);
    data_->eventLoop->RegisterHandler(UpdatePhysicsEvent::type,    this);
    data_->eventLoop->RegisterHandler(PhysicsOverrideEvent::type,  this);
    data_->eventLoop->RegisterHandler(AccelerationEvent::type,     this);
}

Physics::~Physics() {
    // Nop.
}

void Physics::Handle(const ActorCreationEvent &event) {
    int   storageId;
    Actor *newActor = nullptr;
    switch (event.actorType) {
        case LanderActor:
            newActor = landers_.Get(&storageId);
            static_cast<Lander *>(newActor)->SetData(data_);
            break;
            
        case ShotActor:
            newActor = shots_.Get(&storageId);
            static_cast<Shot *>(newActor)->SetData(data_);
            break;
        
        default:
            break;
    }
    
    if (newActor) {
        ActorCreationEvent cookedEvent = event;
        if (!event.launchingActor.IsNone()) {
            ActorInfo<Actor> *info = actorMap_.Get(event.launchingActor);
            assert(info);
            Transform launchingActorTransform;
            info->actor()->GetTransform(&launchingActorTransform);
            Vector launchingActorVelocity;
            info->actor()->GetVelocity(&launchingActorVelocity);
            
            Transform transform = launchingActorTransform;
            transform.SetTranslationPart(Vector());
            Vector initialVelocity = event.initialVelocity;
            transform.ApplyTo(&initialVelocity);
            initialVelocity += launchingActorVelocity;
            
            Transform initialTransform = launchingActorTransform;
            initialTransform.Prepend(event.initialTransform);
            
            cookedEvent = ActorCreationEvent(event.actor, event.actorType, initialTransform, initialVelocity,
                                             ActorName());
        }
        newActor->Handle(cookedEvent);
        actorMap_.Register(cookedEvent.actor, ActorInfo<Actor>(cookedEvent.actorType, storageId, newActor));
    }
}

void Physics::Handle(const ActorTerminationEvent &event) {
    ActorInfo<Actor> *info = actorMap_.Get(event.actor);
    if (info) {
        info->actor()->Handle(event);
        
        switch (info->type()) {
            case LanderActor:
                landers_.Put(info->storageId());
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

void Physics::Handle(const UpdatePhysicsEvent &event) {
    auto now = steady_clock::now();
    int milliSeconds = (int)duration_cast<milliseconds>(now - lastUpdateTime_).count();
    lastUpdateTime_ = now;
    data_->updateDeltaTimeS = (float)milliSeconds / 1000.0f;
    if (emitTimeEvents_) {
        data_->eventLoop->Post(TimeEvent(data_->updateDeltaTimeS));
    }
    
    actions_->Execute();
    data_->eventLoop->Post(PhysicsUpdatedEvent());
}

void Physics::Handle(const PhysicsOverrideEvent &event) {
    ActorInfo<Actor> *info = actorMap_.Get(event.actor);
    if (info) {
        info->actor()->Handle(event);
    }
}

void Physics::Handle(const AccelerationEvent &event) {
    ActorInfo<Actor> *info = actorMap_.Get(event.actor);
    if (info) {
        info->actor()->Handle(event);
    }
}

}    // Namespace Physics.
}    // Namespace Zarch.
}    // Namespace kxm.
