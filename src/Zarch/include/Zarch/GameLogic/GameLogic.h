/*!
 * \ingroup Zarch
 *
 * \defgroup ZarchGameLogic Game Logic
 */

#ifndef KXM_ZARCH_GAMELOGIC_GAMELOGIC_H_
#define KXM_ZARCH_GAMELOGIC_GAMELOGIC_H_

#include <memory>
#include <Game/ActorNaming.h>
#include <Game/ActorMap.h>
#include <Game/ReusableActors.h>
#include <Zarch/ActorInfo.h>
#include <Zarch/Events/ZarchEvent.h>
#include <Zarch/EventHandlerCore.h>

namespace kxm {

namespace Game {
    template<class EventClass, class EventHandlerClass> class EventLoop;
}

namespace Zarch {

class InitializationEvent;
class ShotFiredEvent;

namespace GameLogic {

class Lander;
class Shot;

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
    void Handle(const ShotEvent &event);
    void PrepareMap();
    void CreateLander();
    void CreateShot(const ShotEvent &event);
    //! Terminates the shot if it exists.
    void TerminateShot(const ShotEvent &event);
    void TerminateActor(const Game::ActorName &name);
    
    std::shared_ptr<Game::EventLoop<ZarchEvent, EventHandlerCore>> eventLoop_;
    Game::ActorNaming                                  actorNaming_;
    Game::ActorMap<ActorInfo>                          actorMap_;
    std::shared_ptr<Game::Actions>                     actions_;
    Game::ReusableActors<Lander>                       landers_;
    Game::ReusableActors<Shot>                         shots_;
};

}    // Namespace GameLogic.
}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_GAMELOGIC_GAMELOGIC_H_
