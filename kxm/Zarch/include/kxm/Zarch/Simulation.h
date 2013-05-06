//
//  Simulation.h
//  kxm
//
//  Created by Kai Hergenröther on 4/7/13.
//
//


#ifndef KXM_ZARCH_SIMULATION_H_
#define KXM_ZARCH_SIMULATION_H_


#include <boost/shared_ptr.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>

#include <kxm/Core/ActionInterface.h>
#include <kxm/Game/EventQueue.h>
#include <kxm/Game/Processes.h>
#include <kxm/Zarch/events.h>
#include <kxm/Zarch/processes.h>


namespace kxm {

namespace Game {
    class ThreadCouplingBuffer;
}

namespace Zarch {

class Physics;

//! Ties together the simulation subsytems, that together run on the dedicated simulation thread (as
//! opposed to the main UI thread).
/*!
 *  \ingroup Zarch
 */
class Simulation : public Core::ActionInterface {
  public:
    Simulation(boost::shared_ptr<Game::ThreadCouplingBuffer> presentationCouplingBuffer,
               int sendToPresentationDirection);
    void ExecuteAction();
    
  private:
    Simulation(const Simulation &other);
    Simulation &operator=(const Simulation &other);
    void GenerateTimeEvent();
    
    Game::EventQueue<ZarchEvent::EventType>                        eventQueue_;
    boost::shared_ptr<Game::Processes<ZarchProcess::ProcessType> > processes_;
    ZarchProcess::Context                                          processContext_;
    boost::shared_ptr<Game::ThreadCouplingBuffer>                  presentationCouplingBuffer_;
    int                                                            sendToPresentationDirection_;
    boost::shared_ptr<Physics>                                     physics_;
    boost::posix_time::ptime                                       lastFrameTime_;
};

}
}


#endif    // KXM_ZARCH_SIMULATION_H_

