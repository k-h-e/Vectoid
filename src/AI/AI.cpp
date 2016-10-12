#include <kxm/Zarch/AI/AI.h>

#include <kxm/Game/EventLoop.h>
#include <kxm/Zarch/Events/ActorCreationEvent.h>
#include <kxm/Zarch/Events/ActorTerminationEvent.h>
#include <kxm/Zarch/Events/TriggerEvent.h>
#include <kxm/Zarch/AI/Data.h>

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
    data_->eventLoop = eventLoop;
    
    data_->eventLoop->RegisterHandler(ActorCreationEvent::type,    this);
    data_->eventLoop->RegisterHandler(ActorTerminationEvent::type, this);
    data_->eventLoop->RegisterHandler(TriggerEvent::type,          this);
}

AI::~AI() {
    // Nop.
}

void AI::Handle(const ActorCreationEvent &event) {
}

void AI::Handle(const ActorTerminationEvent &event) {
}

void AI::Handle(const TriggerEvent &event) {
    if ((inTrigger_ != TriggerEvent::NoTrigger) && (event.trigger == inTrigger_)) {
        if (outTrigger_ != TriggerEvent::NoTrigger) {
            data_->eventLoop->Post(TriggerEvent(outTrigger_, event.deltaTime_s));
        }
    }
}

}    // Namespace AI.
}    // Namespace Zarch.
}    // Namespace kxm.
