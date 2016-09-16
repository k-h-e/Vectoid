#include <Zarch/GameLogic/GameLogic.h>

#include <kxm/Core/logging.h>
#include <Game/EventLoop.h>
#include <Game/ReusableActors.h>
#include <Vectoid/Transform.h>
#include <Zarch/MapParameters.h>
#include <Zarch/Events/ZarchEvent.h>
#include <Zarch/Events/InitializationEvent.h>
#include <Zarch/Events/TimeEvent.h>
#include <Zarch/Events/ActorCreationEvent.h>
#include <Zarch/Events/ActorTerminationEvent.h>
#include <Zarch/Events/PhysicsOverrideEvent.h>
#include <Zarch/Events/ControlsEvent.h>
#include <Zarch/GameLogic/Data.h>
#include <Zarch/GameLogic/Lander.h>
#include <Zarch/GameLogic/Shot.h>

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
          data_(new Data()) {
    data_->eventLoop = eventLoop;
    data_->mapParameters = shared_ptr<MapParameters>(new MapParameters());
    
    data_->eventLoop->RegisterHandler(InitializationEvent::type, this);
    data_->eventLoop->RegisterHandler(TimeEvent::type,           this);
    data_->eventLoop->RegisterHandler(ControlsEvent::type,       this);
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

void GameLogic::Handle(const ControlsEvent &event) {
    ActorInfo<EventHandlerCore> *info = actorMap_.Get(event.actor);
    if (info) {
        info->actor()->Handle(event);
    }
}

void GameLogic::PrepareMap() {
    CreateActor(ActorCreationEvent(data_->actorNaming.Get(), LanderActor, Transform(), Vector(), ActorName()));
}

void GameLogic::CreateActor(const ActorCreationEvent &event) {
    EventHandlerCore *actor = nullptr;
    int storageId;
    switch (event.actorType) {
        case LanderActor:
            actor = landers_.Get(&storageId);
            static_cast<Lander *>(actor)->Reset(event.actor, data_);
            break;
            
        case ShotActor:
            actor = shots_.Get(&storageId);
            static_cast<Shot *>(actor)->Reset(event.actor, data_);
            break;
            
        default:
            break;
    }
    if (actor) {
        actorMap_.Register(event.actor, ActorInfo<EventHandlerCore>(event.actorType, storageId, actor));
        data_->eventLoop->Post(event);
    }
}

void GameLogic::TerminateActor(const ActorName &name) {
    ActorInfo<EventHandlerCore> *info = actorMap_.Get(name);
    assert(info);
    switch (info->type()) {
        case ShotActor:
            shots_.Put(info->storageId());
            // Don't use info->actor() below.
            break;
            
        default:
            assert(false);
            break;
    }
    
    actorMap_.Unregister(name);
    data_->actorNaming.Put(name);
    data_->eventLoop->Post(ActorTerminationEvent(name));
}

}    // Namespace GameLogic.
}    // Namespace Zarch.
}    // Namespace kxm.

