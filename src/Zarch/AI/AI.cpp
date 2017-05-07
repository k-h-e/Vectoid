#include <kxm/Zarch/AI/AI.h>

#include <kxm/Game/EventLoop.h>
#include <kxm/Zarch/MapParameters.h>
#include <kxm/Zarch/Terrain.h>
#include <kxm/Zarch/Events/ActorCreationEvent.h>
#include <kxm/Zarch/Events/ActorTerminationEvent.h>
#include <kxm/Zarch/Events/MoveEvent.h>
#include <kxm/Zarch/Events/TriggerEvent.h>
#include <kxm/Zarch/AI/Data.h>
#include <kxm/Zarch/AI/Saucer.h>

using namespace std;
using namespace kxm::Game;

namespace kxm {
namespace Zarch {
namespace AI {

AI::AI(const std::shared_ptr<Game::EventLoop<ZarchEvent, EventHandlerCore>> &eventLoop,
       TriggerEvent::Trigger anInTrigger, TriggerEvent::Trigger anOutTrigger)
        : actions_(new Actions()),
          saucers_(actions_),
          inTrigger_(anInTrigger),
          outTrigger_(anOutTrigger) {
    data_ = make_shared<Data>();
    data_->eventLoop     = eventLoop;
    data_->mapParameters = shared_ptr<MapParameters>(new MapParameters());
    data_->terrain       = make_shared<Terrain>(data_->mapParameters);
    
    data_->eventLoop->RegisterHandler(ActorCreationEvent::type,    this);
    data_->eventLoop->RegisterHandler(ActorTerminationEvent::type, this);
    data_->eventLoop->RegisterHandler(MoveEvent::type,             this);
    data_->eventLoop->RegisterHandler(TriggerEvent::type,          this);
}

AI::~AI() {
    // Nop.
}

void AI::Handle(const ActorCreationEvent &event) {
    Actor *actor = nullptr;
    int   storageId;
    switch (event.actorType) {
        case SaucerActor:
            actor = saucers_.Get(&storageId);
            break;
        default:
            break;
    }
    
    if (actor) {
        actor->SetData(data_);
        actor->Handle(event);
        actorMap_.Register(event.actor, ActorInfo<Actor>(event.actorType, storageId, actor));
    }
}

void AI::Handle(const ActorTerminationEvent &event) {
    ActorInfo<Actor> *info = actorMap_.Get(event.actor);
    if (info) {
        switch (info->Type()) {
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

void AI::Handle(const MoveEvent &event) {
    ActorInfo<Actor> *info = actorMap_.Get(event.actor);
    if (info) {
        info->Actor()->Handle(event);
    }
}

void AI::Handle(const TriggerEvent &event) {
    if ((inTrigger_ != TriggerEvent::NoTrigger) && (event.trigger == inTrigger_)) {
        data_->updateDeltaTime_s = event.deltaTime_s;
        actions_->Execute();
        if (outTrigger_ != TriggerEvent::NoTrigger) {
            data_->eventLoop->Post(TriggerEvent(outTrigger_, event.deltaTime_s));
        }
    }
}

}    // Namespace AI.
}    // Namespace Zarch.
}    // Namespace kxm.
