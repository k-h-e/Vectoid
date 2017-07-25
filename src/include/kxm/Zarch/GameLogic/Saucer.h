#ifndef KXM_ZARCH_GAMELOGIC_SAUCER_H_
#define KXM_ZARCH_GAMELOGIC_SAUCER_H_

#include <kxm/Zarch/GameLogic/Actor.h>

namespace kxm {
namespace Zarch {

class ActorCreationEvent;
class ControlsRequestEvent;

namespace GameLogic {

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
    void Handle(const ControlsRequestEvent &event);
    void HandleCollision(Actor *other);
    void HandleCollision(Lander *lander);
    void HandleCollision(Saucer *saucer);
    void HandleCollision(Shot *shot);
    void HandleGroundCollision();
    void ExecuteAction();
    
  private:
};

}    // Namespace GameLogic.
}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_GAMELOGIC_SAUCER_H_
