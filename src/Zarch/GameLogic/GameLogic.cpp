#include <kxm/Zarch/GameLogic/GameLogic.h>

#include <kxm/Core/logging.h>
#include <kxm/Game/EventLoop.h>
#include <kxm/Game/ReusableActors.h>
#include <kxm/Vectoid/Transform.h>
#include <kxm/Zarch/MapParameters.h>
#include <kxm/Zarch/Terrain.h>
#include <kxm/Zarch/Events/ZarchEvent.h>
#include <kxm/Zarch/Events/InitializationEvent.h>
#include <kxm/Zarch/Events/ActorCreationEvent.h>
#include <kxm/Zarch/Events/ActorTerminationEvent.h>
#include <kxm/Zarch/Events/ControlsRequestEvent.h>
#include <kxm/Zarch/Events/CollisionEvent.h>
#include <kxm/Zarch/Events/GroundCollisionEvent.h>
#include <kxm/Zarch/Events/GroundCollisionEvent.h>
#include <kxm/Zarch/GameLogic/Data.h>
#include <kxm/Zarch/GameLogic/Lander.h>
#include <kxm/Zarch/GameLogic/Shot.h>
#include <kxm/Zarch/GameLogic/Saucer.h>

using namespace std;
using namespace kxm::Core;
using namespace kxm::Game;
using namespace kxm::Vectoid;

namespace kxm {
namespace Zarch {
namespace GameLogic {

GameLogic::GameLogic(const shared_ptr<EventLoop<ZarchEvent, EventHandlerCore>> &eventLoop,
                     TriggerEvent::Trigger anInTrigger, TriggerEvent::Trigger anOutTrigger)
        : actions_(new Actions()),
          landers_(actions_),
          shots_(actions_),
          saucers_(actions_),
          data_(new Data()),
          inTrigger_(anInTrigger),
          outTrigger_(anOutTrigger) {
    data_->eventLoop     = eventLoop;
    data_->mapParameters = shared_ptr<MapParameters>(new MapParameters());
    data_->terrain       = make_shared<Terrain>(data_->mapParameters);
    
    data_->eventLoop->RegisterHandler(InitializationEvent::type,  this);
    data_->eventLoop->RegisterHandler(ControlsRequestEvent::type, this);
    data_->eventLoop->RegisterHandler(TriggerEvent::type,         this);
    data_->eventLoop->RegisterHandler(CollisionEvent::type,       this);
    data_->eventLoop->RegisterHandler(GroundCollisionEvent::type, this);
}

GameLogic::~GameLogic() {
    // Nop.
}

void GameLogic::Handle(const InitializationEvent &event) {
    PrepareMap();
    FinalizeEventHandler();
}

void GameLogic::Handle(const ControlsRequestEvent &event) {
    ActorInfo<Actor> *info = data_->actorMap.Get(event.actor);
    if (info) {
        info->Actor()->Handle(event);
        FinalizeEventHandler();
    }
}

void GameLogic::Handle(const CollisionEvent &event) {
    ActorInfo<Actor> *info      = data_->actorMap.Get(event.actor),
                     *otherInfo = data_->actorMap.Get(event.otherActor);
    if (info && otherInfo) {
        info->Actor()->HandleCollision(otherInfo->Actor());
            // We're using a double dispatch scheme to execute the appropriate code for the pair of collision
            // partners. It is enough to call HandleCollision() on one of them.
        FinalizeEventHandler();
    }
}

void GameLogic::Handle(const GroundCollisionEvent &event) {
    ActorInfo<Actor> *info = data_->actorMap.Get(event.actor);
    if (info) {
        info->Actor()->Handle(event);
        FinalizeEventHandler();
    }
}

void GameLogic::Handle(const TriggerEvent &event) {
    if ((inTrigger_ != TriggerEvent::NoTrigger) && (event.trigger == inTrigger_)) {
        data_->deltaTimeS = event.deltaTime_s;
        actions_->Execute();
        
        if (data_->landerRespawnTimeS != 0.0f) {
            if (data_->landerRespawnTimeS > data_->deltaTimeS) {
                data_->landerRespawnTimeS -= data_->deltaTimeS;
            }
            else {
                data_->landerRespawnTimeS = 0.0f;
                data_->ScheduleActorCreation(ActorCreationEvent(data_->actorNaming.Get(), LanderActor, Transform(),
                                                                Vector(), ActorName()));
            }
        }
        
        FinalizeEventHandler();    // It's okay here for this not to be last action in handler.
        
        if (outTrigger_ != TriggerEvent::NoTrigger) {
            data_->eventLoop->Post(TriggerEvent(outTrigger_, event.deltaTime_s));
        }
    }
}

void GameLogic::FinalizeEventHandler() {
    if (data_->actorCreationEvents.size()) {
        for (ActorCreationEvent &creationEvent : data_->actorCreationEvents) {
            Actor *actor = nullptr;
            int   storageId;
            switch (creationEvent.actorType) {
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
            
            assert(actor);
            data_->actorMap.Register(creationEvent.actor, ActorInfo<Actor>(creationEvent.actorType, storageId, actor));
            data_->eventLoop->Post(creationEvent);
            actor->SetData(data_);
            actor->Handle(creationEvent);
        }
        data_->actorCreationEvents.clear();
    }
    
    if (data_->actorsToTerminate.size()) {
        for (ActorName &name : data_->actorsToTerminate) {
            ActorInfo<Actor> *info = data_->actorMap.Get(name);
            if (info) {
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
                
                data_->actorMap.Unregister(name);
                data_->actorNaming.Put(name);
                data_->eventLoop->Post(ActorTerminationEvent(name));
            }
        }
        data_->actorsToTerminate.clear();
    }
}

void GameLogic::PrepareMap() {
    data_->ScheduleActorCreation(ActorCreationEvent(data_->actorNaming.Get(), LanderActor, Transform(), Vector(),
                                                    ActorName()));
    data_->ScheduleActorCreation(ActorCreationEvent(data_->actorNaming.Get(), SaucerActor,
                                                    Transform(Vector(-1.0f, 3.0f, -2.0f)), Vector(), ActorName()));
}

}    // Namespace GameLogic.
}    // Namespace Zarch.
}    // Namespace kxm.

