//
//  GameLogic.h
//  kxm
//
//  Created by Kai Hergenröther on 12/3/12.
//
//


#ifndef KXM_ZARCH_GAMELOGIC_GAMELOGIC_H_
#define KXM_ZARCH_GAMELOGIC_GAMELOGIC_H_


#include <kxm/Game/EventHandlerInterface.h>


namespace kxm {
namespace Zarch {

//! Game logic subsystem for the <c>Zarch</c> game.
/*!
 *  \ingroup Zarch
 */
class GameLogic : public virtual Game::EventHandlerInterface {
  public:
    GameLogic();
    void HandleEvent(const Game::Event *event);
    void ExecuteProcesses();
    
  private:
    GameLogic(const GameLogic &other);
    GameLogic &operator=(const GameLogic &other);
};

}    // Namespace Zarch.
}    // Namespace kxm.


#endif    // KXM_ZARCH_GAMELOGIC_GAMELOGIC_H_
