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
#include <kxm/Zarch/Events/GroundCollisionEvent.h>
#include <kxm/Zarch/Events/ControlsRequestEvent.h>
#include <kxm/Zarch/Events/ControlsEvent.h>
#include <kxm/Zarch/Events/AccelerationEvent.h>
#include <kxm/Zarch/Events/PlayerStatsEvent.h>
#include <kxm/Zarch/GameLogic/Data.h>

using namespace std;
using namespace kxm::Core;
using namespace kxm::Game;
using namespace kxm::Vectoid;

namespace kxm {
namespace Zarch {
namespace GameLogic {

Lander::Lander(const std::shared_ptr<Data> &data)
        : Actor(data),
          trigger_(false),
          thruster_(false),
          triggerTimeS_(0.0f),
          maxFuel_(2000.0f),
          fuel_(2000.0f),
          fuelConsumptionPerS_(100.0f) {
    // Nop.
}

void Lander::Handle(const ActorCreationEvent &event) {
    Actor::Reset(event);
    trigger_             = false;
    thruster_            = false;
    triggerTimeS_        = 0.0f;
    maxFuel_             = 2000.0f;
    fuel_                = maxFuel_;
    fuelConsumptionPerS_ = 100.0f;
    
    PlayerStatsEvent statsEvent(name_);
    statsEvent.AddStat(PlayerStatsEvent::MaxFuelStat, maxFuel_);
    statsEvent.AddStat(PlayerStatsEvent::FuelStat, fuel_);
    data_->eventLoop->Post(statsEvent);
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
            case ThrusterControl:
                thruster_ = (control.Argument() > .5f) && (fuel_ > 0.0f);
                newEvent.AddControl(Control(ThrusterControl, thruster_ ? 1.0f : 0.0f));
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

void Lander::Handle(const GroundCollisionEvent &event) {
    Vector up(0.0f, 1.0f, 0.0f);
    Transform transform(event.transform);
    transform.SetTranslationPart(Vector());
    transform.ApplyTo(&up);
    if ((up.y < .96f) || (event.velocity.Length() > 2.0f)) {
        std::printf("up.y=%f, v_len=%f\n", up.y, event.velocity.Length());
        data_->ScheduleActorForTermination(name_);
        data_->landerRespawnTimeS = 3.0f;
    }
}

void Lander::HandleCollision(Actor *other) {
    other->HandleCollision(this);
}

void Lander::HandleCollision(Lander *lander) {
    // Nop.
}

void Lander::HandleCollision(Saucer *saucer) {
    // Nop, for now.
}

void Lander::HandleCollision(Shot *shot) {
    // Nop, for now.
}

void Lander::ExecuteAction() {
    PlayerStatsEvent statsEvent(name_);
    
    if (trigger_) {
        triggerTimeS_ += data_->deltaTimeS;
    }
    else {
        triggerTimeS_ = 0.0f;
    }
    
    if (triggerTimeS_ > 0.0f) {
        data_->ScheduleActorCreation(ActorCreationEvent(
            data_->actorNaming.Get(), ShotActor, Transform(Vector(0.0f, 0.0f, .55f)),
            data_->mapParameters->shotVelocity * Vector(0.0f, 0.0f, 1.0f), name_));
        triggerTimeS_ -= data_->mapParameters->shotFiringInterval;
    }
    
    if (thruster_) {
        float oldFuel = fuel_;
        fuel_ -= data_->deltaTimeS * fuelConsumptionPerS_;
        if (fuel_ < 0.0f) {
            ControlsEvent controlsEvent(name_);
            controlsEvent.AddControl(Control(ThrusterControl, 0.0f));
            data_->eventLoop->Post(controlsEvent);
            fuel_     = 0.0f;
            thruster_ = false;
        }
        if (fuel_ != oldFuel) {
            statsEvent.AddStat(PlayerStatsEvent::FuelStat, (int)(fuel_ + .5f));
        }
    }
    
    if (statsEvent.StatCount()) {
        data_->eventLoop->Post(statsEvent);
    }
}

}    // Namespace GameLogic.
}    // Namespace Zarch.
}    // Namespace kxm.