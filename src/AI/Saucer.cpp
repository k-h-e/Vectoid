#include <kxm/Zarch/AI/Saucer.h>

#include <kxm/Core/NumberTools.h>
#include <kxm/Vectoid/Transform.h>
#include <kxm/Game/EventLoop.h>
#include <kxm/Zarch/MapParameters.h>
#include <kxm/Zarch/Terrain.h>
#include <kxm/Zarch/Control.h>
#include <kxm/Zarch/AI/Data.h>
#include <kxm/Zarch/Events/ActorCreationEvent.h>
#include <kxm/Zarch/Events/MoveEvent.h>
#include <kxm/Zarch/Events/ControlsRequestEvent.h>

using namespace std;
using namespace kxm::Core;
using namespace kxm::Game;
using namespace kxm::Vectoid;

namespace kxm {
namespace Zarch {
namespace AI {

Saucer::Saucer()
        : state_(ChooseDestinationState),
          lastDistance_(0.0f),
          randomDistribution_(0, INT_MAX) {
    // Nop.
}

void Saucer::Handle(const ActorCreationEvent &event) {
    Actor::Reset(event);
    state_       = ChooseDestinationState;
    event.initialTransform.GetTranslationPart(&position_);
    destination_ = position_;
    //direction_
    //lastDistance_
}

void Saucer::Handle(const MoveEvent &event) {
    event.transform.GetTranslationPart(&position_);
}

void Saucer::ExecuteAction() {
    static const float maxTravelVelocity =  .4f,
                       travelHeight      = 4.0f,
                       landingHeight     = 1.0f,
                       brakingDistance   = 3.0f,
                       acceleration      =  .2f;
    
    float heightAboveGround = position_.y - data_->terrain->Height(position_.x, position_.z);
    Vector position = position_;
    position.y = 0.0f;
    float distance = (destination_ - position).Length();
    
    switch (state_) {
        case AccelerateState:
            break;
        case TravelState:
            if (distance > lastDistance_) {
                state_ = ChooseDestinationState;
            }
            else {
                ControlsRequestEvent event(name_);
                event.AddControl(Control(Axis1Control, direction_.x));
                event.AddControl(Control(Axis2Control, direction_.z));
                data_->eventLoop->Post(event);
            }
            break;
        case BrakeState:
            break;
        case LandingState:
            break;
        case ChooseDestinationState:
        default:
            do {
                destination_.x = data_->mapParameters->xRange.AffineCombination(
                                    (float)randomDistribution_(randomEngine_) / (float)INT_MAX);
                destination_.z = data_->mapParameters->zRange.AffineCombination(
                                    (float)randomDistribution_(randomEngine_) / (float)INT_MAX);
                direction_     = destination_ - position;
            } while (direction_.Length() < 5.0f);
            direction_.Normalize();
            state_ = TravelState;
            break;
    }
    
    lastDistance_ = distance;
}

}    // Namespace AI.
}    // Namespace Zarch.
}    // Namespace kxm.
