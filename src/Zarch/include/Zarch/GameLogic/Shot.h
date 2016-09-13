#ifndef KXM_ZARCH_GAMELOGIC_SHOT_H_
#define KXM_ZARCH_GAMELOGIC_SHOT_H_

#include <kxm/Core/ActionInterface.h>
#include <Zarch/EventHandlerCore.h>

namespace kxm {
namespace Zarch {
namespace GameLogic {

//! Represents a shot inside the game logic.
/*!
 *  \ingroup ZarchGameLogic
 */
class Shot : public EventHandlerCore, public virtual Core::ActionInterface {
  public:
    Shot();
    Shot(const Shot &other)            = delete;
    Shot &operator=(const Shot &other) = delete;
    Shot(Shot &&other)                 = delete;
    Shot &operator=(Shot &&other)      = delete;
    void Reset();
    void ExecuteAction();
    
  private:
};

}    // Namespace GameLogic.
}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_GAMELOGIC_SHOT_H_