#include <Zarch/GameLogic/GameLogic.h>

#include <kxm/Core/logging.h>
#include <Game/EventLoop.h>
#include <Vectoid/Transform.h>
#include <Zarch/Events/ZarchEvent.h>
#include <Zarch/Events/InitializationEvent.h>
#include <Zarch/Events/ActorCreationEvent.h>
#include <Zarch/Events/ActorTerminationEvent.h>
#include <Zarch/Events/ShotEvent.h>
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

GameLogic::GameLogic(shared_ptr<EventLoop<ZarchEvent, EventHandlerCore>> eventLoop)
        : eventLoop_(eventLoop),
          actions_(new Actions()),
          landers_(actions_),
          shots_(actions_) {
    eventLoop_->RegisterHandler(InitializationEvent::type,  this);
    eventLoop_->RegisterHandler(ShotEvent::type,  this);
}

GameLogic::~GameLogic() {
    // Nop.
}

void GameLogic::Handle(const InitializationEvent &event) {
    PrepareMap();
}

void GameLogic::Handle(const ShotEvent &event) {
    if (event.shotExpired) {
        TerminateShot(event);
    }
    else {
        CreateShot(event);
    }
}

void GameLogic::PrepareMap() {
    CreateLander();
}

void GameLogic::CreateLander() {
    int storageId;
    Lander *lander = landers_.Get(&storageId);
    lander->Reset();
    ActorName name = actorNaming_.Get();
    actorMap_.Register(name, ActorInfo(LanderActor, storageId, lander));
    eventLoop_->Post(ActorCreationEvent(name, LanderActor));
}

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

void GameLogic::TerminateActor(const ActorName &name) {
    actorMap_.Unregister(name);
    actorNaming_.Put(name);
    eventLoop_->Post(ActorTerminationEvent(name));
}

}    // Namespace GameLogic.
}    // Namespace Zarch.
}    // Namespace kxm.

