/*!
 * \ingroup Zarch
 *
 * \defgroup ZarchGameLogic Game Logic
 * \brief Zarch's game logic subsystem.
 */

#ifndef KXM_ZARCH_GAMELOGIC_GAMELOGIC_H_
#define KXM_ZARCH_GAMELOGIC_GAMELOGIC_H_

#include <memory>
#include <kxm/Game/ReusableActors.h>
#include <kxm/Zarch/Events/TriggerEvent.h>
#include <kxm/Zarch/EventHandlerCore.h>
#include <kxm/Zarch/GameLogic/Actor.h>

namespace kxm {

namespace Game {
    template<class EventClass, class EventHandlerClass> class EventLoop;
}

namespace Zarch {

class InitializationEvent;
class ActorCreationEvent;
class ControlsRequestEvent;
class CollisionEvent;
class GroundCollisionEvent;
class TriggerEvent;

namespace GameLogic {

class Data;
class Lander;
class Shot;
class Saucer;

//! Game logic for the <c>Zarch</c> game.
/*!
 *  \ingroup ZarchGameLogic
 */
class GameLogic : public EventHandlerCore {
  public:
    GameLogic(const std::shared_ptr<Game::EventLoop<ZarchEvent, EventHandlerCore>> &eventLoop,
              TriggerEvent::Trigger anInTrigger, TriggerEvent::Trigger anOutTrigger);
    ~GameLogic();
    void Handle(const InitializationEvent &event);
    void Handle(const ControlsRequestEvent &event);
    void Handle(const CollisionEvent &event);
    void Handle(const GroundCollisionEvent &event);
    void Handle(const TriggerEvent &event);
    
  private:
    GameLogic(const GameLogic &other);
    GameLogic &operator=(const GameLogic &other);
    void FinalizeEventHandler();
    void PrepareMap();
    
    std::shared_ptr<Game::Actions>   actions_;
    Game::ReusableActors<Lander>     landers_;
    Game::ReusableActors<Shot>       shots_;
    Game::ReusableActors<Saucer>     saucers_;
    std::shared_ptr<Data>            data_;
    TriggerEvent::Trigger            inTrigger_,
                                     outTrigger_;
    
};

}    // Namespace GameLogic.
}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_GAMELOGIC_GAMELOGIC_H_
