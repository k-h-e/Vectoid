#include <kxm/Zarch/GameLogic/Lander.h>

#include <cstdio>
#include <kxm/Core/NumberTools.h>
#include <kxm/Game/EventLoop.h>
#include <kxm/Game/ActorNaming.h>
#include <kxm/Vectoid/Transform.h>
#include <kxm/Zarch/MapParameters.h>
#include <kxm/Zarch/Events/ActorCreationEvent.h>
#include <kxm/Zarch/Events/MoveEvent.h>
#include <kxm/Zarch/Events/VelocityEvent.h>
#include <kxm/Zarch/Events/ControlsRequestEvent.h>
#include <kxm/Zarch/Events/ControlsEvent.h>
#include <kxm/Zarch/Events/AccelerationEvent.h>
#include <kxm/Zarch/GameLogic/Data.h>

using namespace std;
using namespace kxm::Core;
using namespace kxm::Game;
using namespace kxm::Vectoid;

namespace kxm {
namespace Zarch {
namespace GameLogic {

Lander::Lander()
        : trigger_(false),
          triggerTimeS_(0.0f) {
    // Nop.
}

void Lander::Handle(const ActorCreationEvent &event) {
    Actor::Reset(event);
    trigger_      = false;
    triggerTimeS_ = 0.0f;
}

void Lander::Handle(const ControlsRequestEvent &event) {
    ControlsEvent newEvent(name_);
    Control       control;
    for (int i = 0; i < event.Count(); ++i) {
        event.GetControl(i, &control);
        switch (control.Type()) {
            case TriggerControl:
                trigger_ = (control.Argument() > .5f);
                break;
            default:
                newEvent.AddControl(control);
                break;
        }
    }
    if (newEvent.Count()) {
        data_->eventLoop->Post(newEvent);
    }
}

void Lander::ExecuteAction() {
    if (trigger_) {
        triggerTimeS_ += data_->deltaTimeS;
    }
    else {
        triggerTimeS_ = 0.0f;
    }
    
    if (triggerTimeS_ > 0.0f) {
        data_->actorCreationEvents.push_back(ActorCreationEvent(
            data_->actorNaming.Get(), ShotActor, Transform(Vector(0.0f, 0.0f, .55f)),
            data_->mapParameters->shotVelocity * Vector(0.0f, 0.0f, 1.0f), name_));
        triggerTimeS_ -= data_->mapParameters->shotFiringInterval;
    }
}

}    // Namespace GameLogic.
}    // Namespace Zarch.
}    // Namespace kxm.
