#include <kxm/Zarch/GameLogic/GameLogic.h>

#include <kxm/Core/logging.h>
#include <kxm/Game/EventLoop.h>
#include <kxm/Game/ReusableActors.h>
#include <kxm/Vectoid/Transform.h>
#include <kxm/Zarch/MapParameters.h>
#include <kxm/Zarch/Terrain.h>
#include <kxm/Zarch/Events/ZarchEvent.h>
#include <kxm/Zarch/Events/InitializationEvent.h>
#include <kxm/Zarch/Events/TimeEvent.h>
#include <kxm/Zarch/Events/ActorCreationEvent.h>
#include <kxm/Zarch/Events/ActorTerminationEvent.h>
#include <kxm/Zarch/Events/PhysicsOverrideEvent.h>
#include <kxm/Zarch/Events/MoveEvent.h>
#include <kxm/Zarch/Events/OldControlsEvent.h>
#include <kxm/Zarch/GameLogic/Data.h>
#include <kxm/Zarch/GameLogic/Lander.h>
#include <kxm/Zarch/GameLogic/Shot.h>
#include <kxm/Zarch/GameLogic/Saucer.h>

using namespace std;
using namespace std::chrono;
using namespace kxm::Core;
using namespace kxm::Game;
using namespace kxm::Vectoid;

namespace kxm {
namespace Zarch {
namespace GameLogic {

GameLogic::GameLogic(const shared_ptr<EventLoop<ZarchEvent, EventHandlerCore>> &eventLoop)
        : actions_(new Actions()),
          landers_(actions_),
          shots_(actions_),
          saucers_(actions_),
          data_(new Data()) {
    data_->eventLoop     = eventLoop;
    data_->mapParameters = shared_ptr<MapParameters>(new MapParameters());
    data_->terrain       = make_shared<Terrain>(data_->mapParameters);
    
    data_->eventLoop->RegisterHandler(InitializationEvent::type, this);
    data_->eventLoop->RegisterHandler(TimeEvent::type,           this);
    data_->eventLoop->RegisterHandler(OldControlsEvent::type,    this);
    data_->eventLoop->RegisterHandler(MoveEvent::type,           this);
}

GameLogic::~GameLogic() {
    // Nop.
}

void GameLogic::Handle(const InitializationEvent &event) {
    PrepareMap();
}

void GameLogic::Handle(const TimeEvent &event) {
    data_->deltaTimeS = event.deltaTimeS;
    actions_->Execute();
    
    if (data_->actorCreationEvents.size()) {
        for (ActorCreationEvent &creationEvent : data_->actorCreationEvents) {
            CreateActor(creationEvent);
        }
        data_->actorCreationEvents.clear();
    }
    if (data_->actorsToTerminate.size()) {
        for (ActorName &name : data_->actorsToTerminate) {
            TerminateActor(name);
        }
        data_->actorsToTerminate.clear();
    }
}

void GameLogic::Handle(const OldControlsEvent &event) {
    ActorInfo<Actor> *info = actorMap_.Get(event.actor);
    if (info) {
        info->actor()->Handle(event);
    }
}

void GameLogic::CreateActor(const ActorCreationEvent &event) {
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
    
    assert(actor);
    actor->SetData(data_);
    actor->Handle(event);
    actorMap_.Register(event.actor, ActorInfo<Actor>(event.actorType, storageId, actor));
    data_->eventLoop->Post(event);
}

void GameLogic::TerminateActor(const ActorName &name) {
    ActorInfo<Actor> *info = actorMap_.Get(name);
    assert(info);
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
    
    actorMap_.Unregister(name);
    data_->actorNaming.Put(name);
    data_->eventLoop->Post(ActorTerminationEvent(name));
}

void GameLogic::Handle(const MoveEvent &event) {
    ActorInfo<Actor> *info = actorMap_.Get(event.actor);
    if (info && (info->type() == SaucerActor)) {
        info->actor()->Handle(event);
    }
}

void GameLogic::PrepareMap() {
    CreateActor(ActorCreationEvent(data_->actorNaming.Get(), LanderActor, Transform(), Vector(), ActorName()));
    
    CreateActor(ActorCreationEvent(data_->actorNaming.Get(), SaucerActor, Transform(Vector(-1.0f, 3.0f, -2.0f)),
                                   Vector(), ActorName()));
}

}    // Namespace GameLogic.
}    // Namespace Zarch.
}    // Namespace kxm.

