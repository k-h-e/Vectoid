#include <Zarch/GameLogic/GameLogic.h>

#include <kxm/Core/logging.h>
#include <Game/EventLoop.h>
#include <Vectoid/Transform.h>
#include <Zarch/Events/ZarchEvent.h>
#include <Zarch/Events/InitializationEvent.h>
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
    data_->eventLoop->RegisterHandler(InitializationEvent::type, this);
    data_->eventLoop->RegisterHandler(ControlsEvent::type,       this);
}

GameLogic::~GameLogic() {
    // Nop.
}

void GameLogic::Handle(const InitializationEvent &event) {
    PrepareMap();
}

void GameLogic::Handle(const ControlsEvent &event) {
    ActorInfo *info = actorMap_.Get(event.actor);
    if (info) {
        info->actor()->Handle(event);
    }
}

void GameLogic::PrepareMap() {
    CreateLander();
}

void GameLogic::CreateLander() {
    ActorName name = actorNaming_.Get();
    int storageId;
    Lander *lander = landers_.Get(&storageId);
    lander->Reset(name, data_);
    actorMap_.Register(name, ActorInfo(LanderActor, storageId, lander));
    data_->eventLoop->Post(ActorCreationEvent(name, LanderActor));
}

/*
void GameLogic::CreateShot(const ShotEvent &event) {
    int storageId;
    Shot *shot = shots_.Get(&storageId);
    shot->Reset();
    ActorName name = actorNaming_.Get();
    actorMap_.Register(name, ActorInfo(ShotActor, storageId, shot));
    eventLoop_->Post(ActorCreationEvent(name, ShotActor, Transform(event.shotPosition), event.shotVelocity));
}

void GameLogic::TerminateShot(const ShotEvent &event) {
    ActorInfo *info = actorMap_.Get(event.actor);
    if (info && (info->type() == ShotActor)) {
        shots_.Put(info->storageId());
            // Don't use info->actor() below.
        TerminateActor(event.actor);
    }
}
*/

void GameLogic::TerminateActor(const ActorName &name) {
    actorMap_.Unregister(name);
    actorNaming_.Put(name);
    data_->eventLoop->Post(ActorTerminationEvent(name));
}

}    // Namespace GameLogic.
}    // Namespace Zarch.
}    // Namespace kxm.

