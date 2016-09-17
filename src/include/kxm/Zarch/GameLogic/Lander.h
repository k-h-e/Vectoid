#ifndef KXM_ZARCH_GAMELOGIC_LANDER_H_
#define KXM_ZARCH_GAMELOGIC_LANDER_H_

#include <memory>
#include <kxm/Core/ActionInterface.h>
#include <kxm/Game/ActorName.h>
#include <kxm/Vectoid/Vector.h>
#include <kxm/Zarch/EventHandlerCore.h>

namespace kxm {
namespace Zarch {

class ControlsEvent;

namespace GameLogic {

class Data;

//! Represents a lander inside the game logic.
/*!
 *  \ingroup ZarchGameLogic
 */
class Lander : public EventHandlerCore, public virtual Core::ActionInterface {
  public:
    Lander();
    Lander(const Lander &other)            = delete;
    Lander &operator=(const Lander &other) = delete;
    Lander(Lander &&other)                 = delete;
    Lander &operator=(Lander &&other)      = delete;
    void Reset(const Game::ActorName &name, const std::shared_ptr<Data> &data);
    void Handle(const ControlsEvent &event);
    void ExecuteAction();
    
  private:
    Game::ActorName       name_;
    Vectoid::Vector       heading_;
    bool                  oldThrusterActive_;
    bool                  trigger_;
    float                 triggerTimeS_;
    std::shared_ptr<Data> data_;
};

}    // Namespace GameLogic.
}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_GAMELOGIC_LANDER_H_
