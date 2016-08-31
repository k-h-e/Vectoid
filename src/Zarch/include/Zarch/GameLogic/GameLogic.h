//
//  GameLogic.h
//  kxm
//
//  Created by Kai Hergenröther on 12/3/12.
//
//


#ifndef KXM_ZARCH_GAMELOGIC_GAMELOGIC_H_
#define KXM_ZARCH_GAMELOGIC_GAMELOGIC_H_


#include <memory>
#include <chrono>

#include <Game/ProcessOwnerInterface.h>
#include <Game/ActorNaming.h>
#include <Zarch/Events/ZarchEvent.h>
#include <Zarch/EventHandlerCore.h>


namespace kxm {

namespace Game {
    template<class EventClass, class EventHandlerClass> class EventLoop;
}

namespace Zarch {

class InitializationEvent;
class FrameGeneratedEvent;

//! Game logic for the <c>Zarch</c> game.
/*!
 *  \ingroup Zarch
 */
class GameLogic : public EventHandlerCore,
                  public virtual Game::ProcessOwnerInterface {
  public:
    GameLogic(std::shared_ptr<Game::EventLoop<ZarchEvent, EventHandlerCore>> eventLoop);
    ~GameLogic();
    void HandleProcessFinished(Game::ProcessInterface *process);
    void Handle(const InitializationEvent &event);
    void Handle(const FrameGeneratedEvent &event);
    
  private:
    GameLogic(const GameLogic &other);
    GameLogic &operator=(const GameLogic &other);
    void PrepareMap();
    
    std::shared_ptr<Game::EventLoop<ZarchEvent, EventHandlerCore>> eventLoop_;
    Game::ActorNaming                                              actorNaming_;
    bool                                                           landerThrusterEnabled_,
                                                                   landerFiringEnabled_;
    std::chrono::time_point<std::chrono::steady_clock>             lastFrameTime_;
};

}    // Namespace Zarch.
}    // Namespace kxm.


#endif    // KXM_ZARCH_GAMELOGIC_GAMELOGIC_H_
