#ifndef KXM_ZARCH_GAMELOGIC_ACTOR_H_
#define KXM_ZARCH_GAMELOGIC_ACTOR_H_

#include <memory>
#include <kxm/Core/ActionInterface.h>
#include <kxm/Game/ActorName.h>
#include <kxm/Zarch/EventHandlerCore.h>

namespace kxm {
namespace Zarch {

class ActorCreationEvent;

namespace GameLogic {

class Data;

//! Base class to actors inside the game logic sub system.
/*!
 *  \ingroup ZarchGameLogic
 */
class Actor : public EventHandlerCore, public virtual Core::ActionInterface {
  public:
    // Default copy and move ok.
    void SetData(const std::shared_ptr<Data> &data);
    void Reset(const ActorCreationEvent &event);
    
  protected:
    Game::ActorName       name_;
    std::shared_ptr<Data> data_;
};

}    // Namespace GameLogic
}    // Namespace Zarch
}    // Namespace kxm

#endif    // KXM_ZARCH_GAMELOGIC_ACTOR_H_
