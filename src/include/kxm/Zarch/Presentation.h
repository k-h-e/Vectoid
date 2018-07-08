#ifndef KXM_ZARCH_PRESENTATION_H_
#define KXM_ZARCH_PRESENTATION_H_

#include <memory>

#include <kxm/Zarch/Video/Video.h>
#include <kxm/Zarch/Events/TriggerEvent.h>

namespace kxm {

namespace Game {
    template<class EventClass, class EventHandlerClass> class EventLoop;
    class EventLoopHub;
}

namespace Zarch {

class ControlsState;
class TriggerEvent;

namespace Video {
    class RenderTargetInterface;
}

//! Ties together the presentation subsystems, that together run on the main UI thread.
/*!
 *  \ingroup Zarch
 */
class Presentation : public EventHandlerCore {
  public:
    Presentation(const std::shared_ptr<Game::EventLoopHub> &eventLoopHub,
                 const std::shared_ptr<Video::RenderTargetInterface> &renderTarget);
    ~Presentation();
    void PrepareFrame(const ControlsState &controlsState);
    void SetViewPort(int width, int height);
    void RenderFrame();
    void Handle(const TriggerEvent &event);
    
  private:
    Presentation(const Presentation &other);
    Presentation &operator=(const Presentation &other);
    
    std::shared_ptr<Game::EventLoop<ZarchEvent, EventHandlerCore>> eventLoop_;
    std::shared_ptr<Video::Video>                                  video_;
    TriggerEvent                                                   triggerEvent_;
    TriggerEvent::Trigger                                          lastTrigger_;
};

}
}

#endif    // KXM_ZARCH_PRESENTATION_H_
