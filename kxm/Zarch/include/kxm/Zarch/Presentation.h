//
//  Presentation.h
//  kxm
//
//  Created by Kai Hergenröther on 4/7/13.
//
//


#ifndef KXM_ZARCH_PRESENTATION_H_
#define KXM_ZARCH_PRESENTATION_H_


#include <memory>

#include <kxm/Game/EventQueue.h>
#include <kxm/Game/Processes.h>
#include <kxm/Zarch/Video/Video.h>
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
    Presentation(std::shared_ptr<Game::ThreadCouplingBuffer> simulationCouplingBuffer,
                 int sendToSimulationDirection);
    void PrepareFrame(const ControlsState &controlsState);
    void SetViewPort(int width, int height) { video_->SetViewPort(width, height); }
    void RenderFrame()                      { video_->RenderFrame();              }
    
  private:
    Presentation(const Presentation &other);
    Presentation &operator=(const Presentation &other);
    
    Game::EventQueue<ZarchEvent::EventType>                     eventQueue_;
    std::shared_ptr<Game::Processes<ZarchProcess::ProcessType>> processes_;
    ZarchProcess::Context                                       processContext_;
    std::shared_ptr<Game::ThreadCouplingBuffer>                 simulationCouplingBuffer_;
    int                                                         sendToSimulationDirection_;
    std::shared_ptr<Video>                                      video_;
};

}
}


#endif    // KXM_ZARCH_PRESENTATION_H_
