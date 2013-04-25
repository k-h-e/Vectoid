//
//  Presentation.h
//  kxm
//
//  Created by Kai Hergenröther on 4/7/13.
//
//


#ifndef KXM_ZARCH_PRESENTATION_H_
#define KXM_ZARCH_PRESENTATION_H_


#include <boost/shared_ptr.hpp>

#include <kxm/Game/EventQueue.h>
#include <kxm/Game/Processes.h>
#include <kxm/Zarch/events.h>
#include <kxm/Zarch/processes.h>


namespace kxm {

namespace Game {
    class ThreadCouplingBuffer;
}

namespace Zarch {

class ControlsState;

//! Ties together the presentation subsystems, that together run on the main UI thread.
/*!
 *  \ingroup Zarch
 */
class Presentation {
  public:
    Presentation(boost::shared_ptr<Game::ThreadCouplingBuffer> simulationCouplingBuffer,
                 int sendToSimulationDirection);
    void PrepareFrame(const ControlsState &controlsState);
    void SetViewPort(int width, int height);
    void RenderFrame();
    
  private:
    Presentation(const Presentation &other);
    Presentation &operator=(const Presentation &other);
    
    Game::EventQueue<ZarchEvent::EventType>       eventQueue_;
    Game::Processes<ZarchProcess::ProcessType>    processes_;
    ZarchProcess::Context                         processContext_;
    boost::shared_ptr<Game::ThreadCouplingBuffer> simulationCouplingBuffer_;
    int                                           sendToSimulationDirection_;
};

}
}


#endif    // KXM_ZARCH_PRESENTATION_H_
