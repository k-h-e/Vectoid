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

#include <Game/EventHandlerInterface.h>
#include <Game/ProcessOwnerInterface.h>


namespace kxm {

namespace Game {
    class EventQueueClientInterface;
    class ProcessesClientInterface;
}

namespace Zarch {

class ControlsStateEvent;

//! Game logic for the <c>Zarch</c> game.
/*!
 *  \ingroup Zarch
 */
class GameLogic : public virtual Game::EventHandlerInterface,
                  public virtual Game::ProcessOwnerInterface {
  public:
    GameLogic(std::shared_ptr<Game::EventQueueClientInterface> eventQueue,
              std::shared_ptr<Game::ProcessesClientInterface> processes);
    ~GameLogic();
    std::vector<Game::Event::EventType> EnumerateHandledEvents();
    void HandleProcessFinished(Game::ProcessInterface *process);
    void HandleEvent(const Game::Event &event);
    void HandleControlsStateEvent(const ControlsStateEvent &event);
    
  private:
    GameLogic(const GameLogic &other);
    GameLogic &operator=(const GameLogic &other);
    
    std::shared_ptr<Game::EventQueueClientInterface> eventQueue_;
    std::shared_ptr<Game::ProcessesClientInterface>  processes_;
    bool                                             landerThrusterEnabled_,
                                                     landerFiringEnabled_;
};

}    // Namespace Zarch.
}    // Namespace kxm.


#endif    // KXM_ZARCH_GAMELOGIC_GAMELOGIC_H_
