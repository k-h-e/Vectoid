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
class Lander;
class Saucer;
class Shot;

//! Base class to actors inside the game logic subsystem.
/*!
 *  \ingroup ZarchGameLogic
 */
class Actor : public EventHandlerCore, public virtual Core::ActionInterface {
  public:
    Actor(const std::shared_ptr<Data> &data);
    // Default copy and move ok.
    void Reset(const ActorCreationEvent &event);
    virtual void HandleCollision(Actor *other) = 0;
    virtual void HandleCollision(Lander *lander) = 0;
    virtual void HandleCollision(Saucer *saucer) = 0;
    virtual void HandleCollision(Shot *shot) = 0;
    
  protected:
    Game::ActorName       name_;
    std::shared_ptr<Data> data_;
};

}    // Namespace GameLogic
}    // Namespace Zarch
}    // Namespace kxm

#endif    // KXM_ZARCH_GAMELOGIC_ACTOR_H_
