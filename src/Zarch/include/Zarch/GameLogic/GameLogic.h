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
#include <Zarch/processes.h>


namespace kxm {

namespace Game {
    class EventQueue;
    template<class T> class Processes;
}

namespace Zarch {

class ControlsStateEvent;

//! Game logic for the <c>Zarch</c> game.
/*!
 *  \ingroup Zarch
 */
class GameLogic : public virtual Game::EventHandlerInterface {
  public:
    GameLogic(std::shared_ptr<Game::EventQueue> eventQueue,
              std::shared_ptr<Game::Processes<ZarchProcess::ProcessType>> processes);
    ~GameLogic();
    void HandleEvent(const Game::Event &event);
    void HandleControlsStateEvent(const ControlsStateEvent &event);
    
  private:
    GameLogic(const GameLogic &other);
    GameLogic &operator=(const GameLogic &other);
    
    std::shared_ptr<Game::EventQueue>                           eventQueue_;
    std::shared_ptr<Game::Processes<ZarchProcess::ProcessType>> processes_;
    bool                                                        landerThrusterEnabled_,
                                                                landerFiringEnabled_;
};

}    // Namespace Zarch.
}    // Namespace kxm.


#endif    // KXM_ZARCH_GAMELOGIC_GAMELOGIC_H_
