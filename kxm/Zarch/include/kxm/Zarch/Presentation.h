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
#include <kxm/Zarch/events.h>


namespace kxm {

namespace Game {
    class ThreadCouplingBuffer;
}

namespace Zarch {

//! Ties together the presentation subsystems, that together run on the main UI thread.
/*!
 *  \ingroup Zarch
 */
class Presentation {
  public:
    Presentation(boost::shared_ptr<Game::ThreadCouplingBuffer> simulationCouplingBuffer,
                 int sendToSimulationDirection);
    void PrepareFrame();
    void SetViewPort(int width, int height);
    void RenderFrame();
    
  private:
    Presentation(const Presentation &other);
    Presentation &operator=(const Presentation &other);
    
    Game::EventQueue<ZarchEvent::EventType>       eventQueue_;
    boost::shared_ptr<Game::ThreadCouplingBuffer> simulationCouplingBuffer_;
    int                                           sendToSimulationDirection_;
};

}
}


#endif    // KXM_ZARCH_PRESENTATION_H_
