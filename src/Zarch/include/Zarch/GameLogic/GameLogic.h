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

#include <Game/ProcessOwnerInterface.h>
#include <Zarch/Events/ZarchEvent.h>
#include <Zarch/EventHandlerCore.h>


namespace kxm {

namespace Game {
    template<class EventClass> class EventQueueClientInterface;
    class ProcessesClientInterface;
}

namespace Zarch {

class ControlsStateEvent;

//! Game logic for the <c>Zarch</c> game.
/*!
 *  \ingroup Zarch
 */
class GameLogic : public EventHandlerCore,
                  public virtual Game::ProcessOwnerInterface {
  public:
    GameLogic(std::shared_ptr<Game::EventQueueClientInterface<ZarchEvent>> eventQueue,
              std::shared_ptr<Game::ProcessesClientInterface> processes);
    ~GameLogic();
    std::vector<Game::Event::EventType> EnumerateHandledEvents();
    void HandleProcessFinished(Game::ProcessInterface *process);
    void HandleControlsStateEvent(const ControlsStateEvent &event);
    
  private:
    GameLogic(const GameLogic &other);
    GameLogic &operator=(const GameLogic &other);
    
    std::shared_ptr<Game::EventQueueClientInterface<ZarchEvent>> eventQueue_;
    std::shared_ptr<Game::ProcessesClientInterface>              processes_;
    bool                                                         landerThrusterEnabled_,
                                                                 landerFiringEnabled_;
};

}    // Namespace Zarch.
}    // Namespace kxm.


#endif    // KXM_ZARCH_GAMELOGIC_GAMELOGIC_H_
