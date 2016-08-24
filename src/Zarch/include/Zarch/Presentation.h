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

#include <Zarch/Video/Video.h>
#include <Zarch/Events/FrameGeneratedEvent.h>

namespace kxm {

namespace Game {
    template<class EventClass, class EventHandlerClass> class EventLoop;
    class Processes;
    class EventLoopHub;
}

namespace Zarch {

class ControlsState;

//! Ties together the presentation subsystems, that together run on the main UI thread.
/*!
 *  \ingroup Zarch
 */
class Presentation {
  public:
    Presentation(const std::shared_ptr<Game::EventLoopHub> &eventLoopHub);
    ~Presentation();
    void PrepareFrame(const ControlsState &controlsState);
    void SetViewPort(int width, int height);
    void RenderFrame();
    
  private:
    Presentation(const Presentation &other);
    Presentation &operator=(const Presentation &other);
    
    std::shared_ptr<Game::EventLoop<ZarchEvent, EventHandlerCore>> eventLoop_;
    std::shared_ptr<Game::Processes>                               processes_;
    std::shared_ptr<Video>                                         video_;
    FrameGeneratedEvent                                            frameGeneratedEvent_;
};

}
}

#endif    // KXM_ZARCH_PRESENTATION_H_
