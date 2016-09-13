#ifndef KXM_ZARCH_GAMELOGIC_LANDER_H_
#define KXM_ZARCH_GAMELOGIC_LANDER_H_

#include <kxm/Core/ActionInterface.h>
#include <Zarch/EventHandlerCore.h>

namespace kxm {
namespace Zarch {
namespace GameLogic {

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
    void Reset();
    void ExecuteAction();
    
  private:
};

}    // Namespace GameLogic.
}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_GAMELOGIC_LANDER_H_