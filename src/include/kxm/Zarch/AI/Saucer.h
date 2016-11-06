#ifndef KXM_ZARCH_AI_SAUCER_H_
#define KXM_ZARCH_AI_SAUCER_H_

#include <memory>
#include <random>
#include <kxm/Vectoid/Vector.h>
#include <kxm/Zarch/AI/Actor.h>

namespace kxm {
namespace Zarch {

class ActorCreationEvent;
class MoveEvent;

namespace AI {

class Data;

//! Represents an enemy saucer inside the AI subsystem.
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
                 TravelState };
  
    State                           state_;
    Vectoid::Vector                 position_,
                                    destinationXZ_,
                                    direction_;
    std::default_random_engine      randomEngine_;
    std::uniform_int_distribution<> randomDistribution_;
};

}    // Namespace AI.
}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_AI_SAUCER_H_
