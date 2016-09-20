#ifndef KXM_ZARCH_GAMELOGIC_LANDER_H_
#define KXM_ZARCH_GAMELOGIC_LANDER_H_

#include <memory>
#include <kxm/Vectoid/Transform.h>
#include <kxm/Zarch/GameLogic/Actor.h>

namespace kxm {
namespace Zarch {

class ActorCreationEvent;
class MoveEvent;
class ControlsEvent;

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
    void Handle(const ControlsEvent &event);
    void ExecuteAction();
    
  private:
    Vectoid::Vector       heading_;
    bool                  oldThrusterActive_;
    bool                  trigger_;
    float                 triggerTimeS_;
};

}    // Namespace GameLogic.
}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_GAMELOGIC_LANDER_H_
