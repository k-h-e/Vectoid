#include <Zarch/GameLogic/GameLogic.h>

#include <kxm/Core/logging.h>
#include <Game/EventLoop.h>
#include <Zarch/Events/ZarchEvent.h>
#include <Zarch/Events/InitializationEvent.h>
#include <Zarch/Events/ActorCreatedEvent.h>

using namespace std;
using namespace std::chrono;
using namespace kxm::Core;
using namespace kxm::Game;

namespace kxm {
namespace Zarch {
namespace GameLogic {

GameLogic::GameLogic(shared_ptr<EventLoop<ZarchEvent, EventHandlerCore>> eventLoop)
        : eventLoop_(eventLoop),
          landerThrusterEnabled_(false),
          landerFiringEnabled_(false) {
    eventLoop_->RegisterHandler(InitializationEvent::type,  this);
}

GameLogic::~GameLogic() {
    // Nop.
}

void GameLogic::Handle(const InitializationEvent &event) {
    PrepareMap();
}

void GameLogic::PrepareMap() {
    ActorName landerActor = actorNaming_.Get();
    eventLoop_->Post(ActorCreatedEvent(landerActor, LanderActor));
}

}    // Namespace GameLogic.
}    // Namespace Zarch.
}    // Namespace kxm.

