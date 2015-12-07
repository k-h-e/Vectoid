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


namespace kxm {

namespace Game {
    class EventQueue;
    class Processes;
    class EventQueueHub;
}

namespace Zarch {

class ControlsState;

//! Ties together the presentation subsystems, that together run on the main UI thread.
/*!
 *  \ingroup Zarch
 */
class Presentation {
  public:
    Presentation(const std::shared_ptr<Game::EventQueueHub> &eventQueueHub);
    ~Presentation();
    void PrepareFrame(const ControlsState &controlsState);
    void SetViewPort(int width, int height) { video_->SetViewPort(width, height); }
    void RenderFrame()                      { video_->RenderFrame();              }
    
  private:
    Presentation(const Presentation &other);
    Presentation &operator=(const Presentation &other);
    
    std::shared_ptr<Game::EventQueue> eventQueue_;
    std::shared_ptr<Game::Processes>  processes_;
    std::shared_ptr<Video>            video_;
};

}
}


#endif    // KXM_ZARCH_PRESENTATION_H_
