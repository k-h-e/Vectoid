/*!
 * \ingroup Zarch
 *
 * \defgroup ZarchVideo Video
 */

#ifndef KXM_ZARCH_VIDEO_H_
#define KXM_ZARCH_VIDEO_H_

#include <memory>
#include <chrono>

#include <Game/ProcessOwnerInterface.h>
#include <Game/Actors.h>
#include <Vectoid/Vector.h>
#include <Zarch/EventHandlerCore.h>
#include <Zarch/Events/ZarchEvent.h>
#include <Zarch/Video/Data.h>

namespace kxm {

namespace Game {
    template<class EventClass, class EventHandleClass> class EventLoop;
}

namespace Zarch {

class ActorCreatedEvent;
class MoveEvent;
class LanderVelocityEvent;
class LanderThrusterEvent;
class EventHandlerCore;

namespace Video {

class Lander;
class StarFieldProcess;

//! Video subsystem for the <c>Zarch</c> game.
/*!
 *  \ingroup ZarchVideo
 */
class Video : public EventHandlerCore,
              public virtual Game::ProcessOwnerInterface {
  public:
    Video(std::shared_ptr<Game::EventLoop<ZarchEvent, EventHandlerCore>> eventLoop);
    ~Video();
    //! Reconfigures the video system for the specified view port dimensions.
    void SetViewPort(int width, int height);
    void HandleProcessFinished(Game::ProcessInterface *process);
    void Handle(const ActorCreatedEvent &event);
    void Handle(const FrameGeneratedEvent &event);
    void Handle(const MoveEvent &event);
    void Handle(const LanderVelocityEvent &event);
    void Handle(const LanderThrusterEvent &event);
  
  private:
    Video(const Video &other);
    Video &operator=(const Video &other);
    
    std::shared_ptr<Game::EventLoop<ZarchEvent, EventHandlerCore>> eventLoop_;
    std::shared_ptr<Data>                                          data_;
    std::unique_ptr<StarFieldProcess>                              starFieldProcess_;
    Game::Actors<EventHandlerCore>                                 actors_;
    std::unique_ptr<Lander>                                        lander_;
    bool                                                           landerInUse_;
    std::chrono::time_point<std::chrono::steady_clock>             lastFrameTime_;
};

}    // Namespace Video.
}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_VIDEO_H_
