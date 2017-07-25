#ifndef KXM_ZARCH_GAMELOGIC_LANDER_H_
#define KXM_ZARCH_GAMELOGIC_LANDER_H_

#include <memory>
#include <kxm/Zarch/GameLogic/Actor.h>

namespace kxm {
namespace Zarch {

class ActorCreationEvent;
class ControlsRequestEvent;

namespace GameLogic {

class Data;

//! Represents a lander inside the game logic.
/*!
 *  \ingroup ZarchGameLogic
 */
class Lander : public Actor {
  public:
    Lander();
    Lander(const Lander &other)            = delete;
    Lander &operator=(const Lander &other) = delete;
    Lander(Lander &&other)                 = delete;
    Lander &operator=(Lander &&other)      = delete;
    void Handle(const ActorCreationEvent &event);
    void Handle(const ControlsRequestEvent &event);
    void HandleCollision(Actor *other);
    void HandleCollision(Lander *lander);
    void HandleCollision(Saucer *saucer);
    void HandleCollision(Shot *shot);
    void HandleGroundCollision();
    void ExecuteAction();
    
  private:
    bool  trigger_,
          thruster_;
    float triggerTimeS_;
    float fuel_,
          maxFuel_,
          fuelConsumptionPerS_;
};

}    // Namespace GameLogic.
}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_GAMELOGIC_LANDER_H_
