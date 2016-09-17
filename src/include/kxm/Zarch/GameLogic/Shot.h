#ifndef KXM_ZARCH_GAMELOGIC_SHOT_H_
#define KXM_ZARCH_GAMELOGIC_SHOT_H_

#include <memory>
#include <kxm/Core/ActionInterface.h>
#include <kxm/Game/ActorName.h>
#include <kxm/Zarch/EventHandlerCore.h>

namespace kxm {
namespace Zarch {
namespace GameLogic {

class Data;

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
    void Reset(const Game::ActorName &name, const std::shared_ptr<Data> &data);
    void ExecuteAction();
    
  private:
    Game::ActorName       name_;
    float                 ageS_;
    std::shared_ptr<Data> data_;
};

}    // Namespace GameLogic.
}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_GAMELOGIC_SHOT_H_
