/*!
 * \ingroup Zarch
 *
 * \defgroup ZarchGameLogic Game Logic
 */

#ifndef KXM_ZARCH_GAMELOGIC_GAMELOGIC_H_
#define KXM_ZARCH_GAMELOGIC_GAMELOGIC_H_

#include <memory>
#include <Game/ActorNaming.h>
#include <Zarch/Events/ZarchEvent.h>
#include <Zarch/EventHandlerCore.h>

namespace kxm {

namespace Game {
    template<class EventClass, class EventHandlerClass> class EventLoop;
}

namespace Zarch {

class InitializationEvent;

namespace GameLogic {

//! Game logic for the <c>Zarch</c> game.
/*!
 *  \ingroup ZarchGameLogic
 */
class GameLogic : public EventHandlerCore {
  public:
    GameLogic(std::shared_ptr<Game::EventLoop<ZarchEvent, EventHandlerCore>> eventLoop);
    ~GameLogic();
    void Handle(const InitializationEvent &event);
    
  private:
    GameLogic(const GameLogic &other);
    GameLogic &operator=(const GameLogic &other);
    void PrepareMap();
    
    std::shared_ptr<Game::EventLoop<ZarchEvent, EventHandlerCore>> eventLoop_;
    Game::ActorNaming                                              actorNaming_;
    bool                                                           landerThrusterEnabled_,
                                                                   landerFiringEnabled_;
};

}    // Namespace GameLogic.
}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_GAMELOGIC_GAMELOGIC_H_
