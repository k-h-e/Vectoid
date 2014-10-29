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
#include <kxm/Game/OldEventQueue.h>
#include <kxm/Game/Processes.h>
#include <kxm/Zarch/events.h>
#include <kxm/Zarch/processes.h>


namespace kxm {

namespace Game {
    class ThreadCouplingBuffer;
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
    Simulation(std::shared_ptr<Game::ThreadCouplingBuffer> presentationCouplingBuffer,
               int sendToPresentationDirection);
    void ExecuteAction();
    
  private:
    Simulation(const Simulation &other);
    Simulation &operator=(const Simulation &other);
    void GenerateTimeEvent();
    
    Game::OldEventQueue<OldZarchEvent::EventType>               eventQueue_;
    std::shared_ptr<Game::Processes<ZarchProcess::ProcessType>> processes_;
    ZarchProcess::Context                                       processContext_;
    std::shared_ptr<Game::ThreadCouplingBuffer>                 presentationCouplingBuffer_;
    int                                                         sendToPresentationDirection_;
    std::shared_ptr<GameLogic>                                  gameLogic_;
    std::shared_ptr<Physics>                                    physics_;
    std::chrono::time_point<std::chrono::steady_clock>          lastFrameTime_;
};

}
}


#endif    // KXM_ZARCH_SIMULATION_H_

