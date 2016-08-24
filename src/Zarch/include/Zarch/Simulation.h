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

#include <kxm/Core/ActionInterface.h>
#include <Zarch/Events/ZarchEvent.h>
#include <Zarch/EventHandlerCore.h>


namespace kxm {

namespace Game {
    template<class EventClass, class EventHandlerClass> class EventLoop;
    class Processes;
    class EventLoopHub;
}

namespace Zarch {

class GameLogic;
class Physics;

//! Ties together the simulation subsytems, that together run on the dedicated simulation thread (as
//! opposed to the main UI thread).
/*!
 *  \ingroup Zarch
 */
class Simulation : public virtual Core::ActionInterface {
  public:
    Simulation(const std::shared_ptr<Game::EventLoopHub> &eventLoopHub);
    ~Simulation();
    void ExecuteAction();
    
  private:
    Simulation(const Simulation &other);
    Simulation &operator=(const Simulation &other);
    
    std::shared_ptr<Game::EventLoop<ZarchEvent, EventHandlerCore>> eventLoop_;
    std::shared_ptr<Game::Processes>                               processes_;
    std::shared_ptr<GameLogic>                                     gameLogic_;
    std::shared_ptr<Physics>                                       physics_;
};

}
}


#endif    // KXM_ZARCH_SIMULATION_H_

