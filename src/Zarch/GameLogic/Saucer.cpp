#include <kxm/Zarch/GameLogic/Saucer.h>

#include <kxm/Game/EventLoop.h>
#include <kxm/Zarch/GameLogic/Data.h>
#include <kxm/Zarch/GameLogic/Lander.h>
#include <kxm/Zarch/Events/ActorCreationEvent.h>
#include <kxm/Zarch/Events/ControlsRequestEvent.h>
#include <kxm/Zarch/Events/ControlsEvent.h>

using namespace std;
using namespace kxm::Vectoid;
using namespace kxm::Game;

namespace kxm {
namespace Zarch {
namespace GameLogic {

Saucer::Saucer() {
    // Nop.
}

void Saucer::Handle(const ActorCreationEvent &event) {
    Actor::Reset(event);
}

void Saucer::Handle(const ControlsRequestEvent &event) {
    ControlsEvent newEvent(name_);
    Control       control;
    for (int i = 0; i < event.Count(); ++i) {
        event.GetControl(i, &control);
        switch (control.Type()) {
            default:
                newEvent.AddControl(control);
                break;
        }
    }
    if (newEvent.Count()) {
        data_->eventLoop->Post(newEvent);
    }
}

void Saucer::HandleCollision(Actor *other) {
    other->HandleCollision(this);
}

void Saucer::HandleCollision(Lander *lander) {
    lander->HandleCollision(this);
}

void Saucer::HandleCollision(Saucer *saucer) {
    // Nop.
}

void Saucer::HandleCollision(Shot *shot) {
    data_->ScheduleActorForTermination(name_);
    data_->ScheduleActorCreation(ActorCreationEvent(data_->actorNaming.Get(), SaucerActor,
                                 Transform(Vector(-1.0f, 3.0f, -2.0f)), Vector(), ActorName()));
}

void Saucer::ExecuteAction() {
    // Nop.
}

}    // Namespace GameLogic.
}    // Namespace Zarch.
}    // Namespace kxm.
