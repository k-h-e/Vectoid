#include <kxm/Zarch/GameLogic/Saucer.h>

#include <kxm/Core/NumberTools.h>
#include <kxm/Vectoid/Transform.h>
#include <kxm/Game/EventLoop.h>
#include <kxm/Zarch/MapParameters.h>
#include <kxm/Zarch/Terrain.h>
#include <kxm/Zarch/GameLogic/Data.h>
#include <kxm/Zarch/Events/AccelerationEvent.h>
#include <kxm/Zarch/Events/PhysicsOverrideEvent.h>
#include <kxm/Zarch/Events/MoveEvent.h>

using namespace std;
using namespace kxm::Core;
using namespace kxm::Game;
using namespace kxm::Vectoid;

namespace kxm {
namespace Zarch {
namespace GameLogic {

Saucer::Saucer()
        : state_(ChooseDestinationState),
          travelVelocity_(0.0f),
          targetHeight_(0.0f),
          lastDistance_(0.0f),
          angle_(0.0f),
          angularVelocity_(10.0f),
          randomDistribution_(0, INT_MAX) {
    // Nop.
}

void Saucer::Handle(const ActorCreationEvent &event) {
    Actor::Reset(event);
    state_           = ChooseDestinationState;
    //destination_
    //direction_
    event.initialTransform.GetTranslationPart(&position_);
    velocity_        = Vector();
    //distanceLeftToTravel_
    //travelVelocity_
    //targetHeight_
    //lastDistance_
    angle_           = 0.0f;
    angularVelocity_ = 30.0f;
}

void Saucer::Handle(const MoveEvent &event) {
    event.transform.GetTranslationPart(&position_);
}

void Saucer::ExecuteAction() {
    static const float maxTravelVelocity =  .4f,
                       travelHeight      = 4.0f,
                       landingHeight     = 1.0f,
                       brakingDistance   = 3.0f,
                       acceleration      =  .2f,
                       verticalVelocity  =  .15f;
    
    // Do AI...
    float heightAboveGround = position_.y - data_->terrain->Height(position_.x, position_.z);
    Vector position = position_;
    position.y = 0.0f;
    float distance = (destination_ - position).Length();
    switch (state_) {
        case AccelerateState:
            if (travelVelocity_ >= maxTravelVelocity) {
                state_ = TravelState;
            }
            else {
                travelVelocity_ += data_->deltaTimeS * acceleration;
            }
            break;
        case TravelState:
            if (distance < brakingDistance) {
                targetHeight_ = landingHeight;
                lastDistance_ = distance;
                state_        = BrakeState;
            }
            break;
        case BrakeState:
            if (!(distance < lastDistance_)) {
                travelVelocity_ = 0.0f;
                state_          = LandingState;
            }
            else {
                float t = 1.0f - distance/brakingDistance;
                t *= t;
                travelVelocity_ = (1.0f - t)*maxTravelVelocity + t*.1f;
                lastDistance_ = distance;
            }
            break;
        case LandingState:
            if (heightAboveGround <= targetHeight_ + .1f) {
                state_ = ChooseDestinationState;
            }
            break;
        case ChooseDestinationState:
        default:
            do {
                destination_.x = data_->mapParameters->xRange.AffineCombination(
                                    (float)randomDistribution_(randomEngine_) / (float)INT_MAX);
                destination_.z = data_->mapParameters->zRange.AffineCombination(
                                    (float)randomDistribution_(randomEngine_) / (float)INT_MAX);
                direction_            = destination_ - position;
            } while (direction_.Length() < 5.0f);
            direction_.Normalize();
            travelVelocity_ = 0.0f;
            targetHeight_   = travelHeight;
            state_ = AccelerateState;
            break;
    }
    
    velocity_ = travelVelocity_ * direction_;
    if (heightAboveGround < targetHeight_ - .1f) {
        velocity_.y = verticalVelocity;
    }
    else if (heightAboveGround > targetHeight_ + .1f) {
        velocity_.y = -verticalVelocity;
    }
    else {
        velocity_.y = 0.0f;
    }
    
    // Do rotation...
    angle_ += data_->deltaTimeS * angularVelocity_;
    while (angle_ > 360.0f) {
        angle_ -= 360.0f;
    }
    
    Transform transform(YAxis, angle_);
    data_->eventLoop->Post(PhysicsOverrideEvent(name_, transform, velocity_));
}

}    // Namespace GameLogic.
}    // Namespace Zarch.
}    // Namespace kxm.
