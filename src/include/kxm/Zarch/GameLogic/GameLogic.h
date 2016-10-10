/*!
 * \ingroup Zarch
 *
 * \defgroup ZarchGameLogic Game Logic
 */

#ifndef KXM_ZARCH_GAMELOGIC_GAMELOGIC_H_
#define KXM_ZARCH_GAMELOGIC_GAMELOGIC_H_

#include <memory>
#include <kxm/Game/ActorMap.h>
#include <kxm/Game/ReusableActors.h>
#include <kxm/Zarch/ActorInfo.h>
#include <kxm/Zarch/Events/ZarchEvent.h>
#include <kxm/Zarch/EventHandlerCore.h>
#include <kxm/Zarch/GameLogic/Actor.h>

namespace kxm {

namespace Game {
    template<class EventClass, class EventHandlerClass> class EventLoop;
}

namespace Zarch {

class InitializationEvent;
class ActorCreationEvent;
class MoveEvent;
class TimeEvent;
class ControlsRTequestEvent;

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
    GameLogic(const std::shared_ptr<Game::EventLoop<ZarchEvent, EventHandlerCore>> &eventLoop);
    ~GameLogic();
    void Handle(const InitializationEvent &event);
    
  private:
    GameLogic(const GameLogic &other);
    GameLogic &operator=(const GameLogic &other);
    void Handle(const MoveEvent &event);
    void Handle(const TimeEvent &event);
    void Handle(const ControlsRequestEvent &event);
    void CreateActor(const ActorCreationEvent &event);
    void TerminateActor(const Game::ActorName &name);
    void PrepareMap();
    
    Game::ActorMap<ActorInfo<Actor>> actorMap_;
    std::shared_ptr<Game::Actions>   actions_;
    Game::ReusableActors<Lander>     landers_;
    Game::ReusableActors<Shot>       shots_;
    Game::ReusableActors<Saucer>     saucers_;
    std::shared_ptr<Data>            data_;
};

}    // Namespace GameLogic.
}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_GAMELOGIC_GAMELOGIC_H_
