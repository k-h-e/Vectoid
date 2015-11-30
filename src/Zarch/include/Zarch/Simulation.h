//
//  Simulation.h
//  kxm
//
//  Created by Kai Hergenröther on 4/7/13.
//
//


#ifndef KXM_ZARCH_SIMULATION_H_
#define KXM_ZARCH_SIMULATION_H_


#include <memory>
#include <chrono>

#include <kxm/Core/ActionInterface.h>
#include <Game/EventQueue.h>
#include <Game/Processes.h>
#include <Zarch/processes.h>


namespace kxm {

namespace Game {
    class EventQueueHub;
}

namespace Zarch {

class GameLogic;
class Physics;

//! Ties together the simulation subsytems, that together run on the dedicated simulation thread (as
//! opposed to the main UI thread).
/*!
 *  \ingroup Zarch
 */
class Simulation : public Core::ActionInterface {
  public:
    Simulation(const std::shared_ptr<Game::EventQueueHub> &eventQueueHub);
    void ExecuteAction();
    
  private:
    Simulation(const Simulation &other);
    Simulation &operator=(const Simulation &other);
    void GenerateTimeEvent();
    
    std::shared_ptr<Game::EventQueue>                           eventQueue_;
    std::shared_ptr<Game::Processes<ZarchProcess::ProcessType>> processes_;
    std::shared_ptr<GameLogic>                                  gameLogic_;
    std::shared_ptr<Physics>                                    physics_;
    std::chrono::time_point<std::chrono::steady_clock>          lastFrameTime_;
};

}
}


#endif    // KXM_ZARCH_SIMULATION_H_

