#ifndef KXM_ZARCH_GAMELOGIC_SAUCER_H_
#define KXM_ZARCH_GAMELOGIC_SAUCER_H_

#include <memory>
#include <random>
#include <kxm/Vectoid/Transform.h>
#include <kxm/Zarch/GameLogic/Actor.h>

namespace kxm {
namespace Zarch {

class ActorCreationEvent;
class MoveEvent;

namespace GameLogic {

class Data;

//! Represents an enemy saucer inside the game logic.
/*!
 *  \ingroup ZarchGameLogic
 */
class Saucer : public Actor {
  public:
    Saucer();
    Saucer(const Saucer &other)            = delete;
    Saucer &operator=(const Saucer &other) = delete;
    Saucer(Saucer &&other)                 = delete;
    Saucer &operator=(Saucer &&other)      = delete;
    void Handle(const ActorCreationEvent &event);
    void Handle(const MoveEvent &event);
    void ExecuteAction();
    
  private:
    enum State { ChooseDestinationState,
                 AccelerateState,
                 TravelState,
                 BrakeState,
                 LandingState };
  
    State                           state_;
    Vectoid::Vector                 destination_,
                                    direction_,
                                    position_,
                                    velocity_;
    float                           travelVelocity_,
                                    targetHeight_,
                                    lastDistance_;
    float                           angle_,
                                    angularVelocity_;
    std::default_random_engine      randomEngine_;
    std::uniform_int_distribution<> randomDistribution_;
};

}    // Namespace GameLogic.
}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_GAMELOGIC_SAUCER_H_
