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

Saucer::Saucer(const std::shared_ptr<Data> &data)
        : Actor(data),
          state_(ChooseDestinationState),
          randomDistribution_(0, INT_MAX) {
    // Nop.
}

void Saucer::Handle(const ActorCreationEvent &event) {
    Actor::Reset(event);
    state_           = ChooseDestinationState;
    event.initialTransform.GetTranslationPart(&position_);
    destinationXZ_   = position_;
    destinationXZ_.y = 0.0f;
}

void Saucer::Handle(const MoveEvent &event) {
    event.transform.GetTranslationPart(&position_);
}

void Saucer::ExecuteAction() {
    static const float travelHeight      = 4.0,
                       arrivalHeight     = 1.0,
                       heightHysteresis  =  .2,
                       brakingDistance   = 3.0f,
                       arrivalDistance   =  .1f;
    
    float groundY = data_->terrain->Height(position_.x, position_.z);
    Vector positionXZ = position_;
    positionXZ.y      = 0.0f;
    float distance = (destinationXZ_ - positionXZ).Length();
    
    switch (state_) {
        case TravelState:
            if (distance <= arrivalDistance) {
                state_ = ChooseDestinationState;
            }
            else {
                Vector velocity = direction_;
                float  height   = travelHeight;
                if (distance <= brakingDistance) {
                    float t = distance / brakingDistance;
                    velocity = t * velocity;
                    height   = (1.0f - t)*arrivalHeight + t*travelHeight;
                }
                float thruster = 0.0f,
                      desiredY = groundY + height;
                if (position_.y < desiredY - heightHysteresis) {
                    thruster = 1.0f;
                }
                else if (position_.y > desiredY + heightHysteresis) {
                    thruster = -1.0f;
                }
                
                ControlsRequestEvent event(name_);
                event.AddControl(Control(Axis1Control,    velocity.x));
                event.AddControl(Control(Axis2Control,    velocity.z));
                event.AddControl(Control(ThrusterControl, thruster));
                data_->eventLoop->Post(event);
            }
            break;
        case ChooseDestinationState:
        default:
            do {
                destinationXZ_.x = data_->mapParameters->xRange.AffineCombination(
                                       (float)randomDistribution_(randomEngine_) / (float)INT_MAX);
                destinationXZ_.z = data_->mapParameters->zRange.AffineCombination(
                                       (float)randomDistribution_(randomEngine_) / (float)INT_MAX);
                destinationXZ_.y = 0.0f;
                direction_       = destinationXZ_ - positionXZ;
            } while (direction_.Length() < 5.0f);
            direction_.Normalize();
            std::printf("saucer: direction=(%f, %f)\n", direction_.x, direction_.z);
            state_ = TravelState;
            break;
    }
}

}    // Namespace AI.
}    // Namespace Zarch.
}    // Namespace kxm.
