/*!
 * \ingroup Zarch
 *
 * \defgroup ZarchGameLogic Game Logic
 */

#ifndef KXM_ZARCH_GAMELOGIC_GAMELOGIC_H_
#define KXM_ZARCH_GAMELOGIC_GAMELOGIC_H_

#include <memory>
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
class ActorCreationEvent;
class TimeEvent;
class ControlsEvent;

namespace GameLogic {

class Data;
class Lander;
class Shot;

//! Game logic for the <c>Zarch</c> game.
/*!
 *  \ingroup ZarchGameLogic
 */
class GameLogic : public EventHandlerCore {
  public:
    GameLogic(const std::shared_ptr<Game::EventLoop<ZarchEvent, EventHandlerCore>> &eventLoop);
    ~GameLogic();
    void Handle(const InitializationEvent &event);
    
  private:
    GameLogic(const GameLogic &other);
    GameLogic &operator=(const GameLogic &other);
    void Handle(const TimeEvent &event);
    void Handle(const ControlsEvent &event);
    void PrepareMap();
    void CreateActor(const ActorCreationEvent &event);
    void TerminateActor(const Game::ActorName &name);
    
    Game::ActorMap<ActorInfo<EventHandlerCore>> actorMap_;
    std::shared_ptr<Game::Actions>              actions_;
    Game::ReusableActors<Lander>                landers_;
    Game::ReusableActors<Shot>                  shots_;
    std::shared_ptr<Data>                       data_;
};

}    // Namespace GameLogic.
}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_GAMELOGIC_GAMELOGIC_H_
