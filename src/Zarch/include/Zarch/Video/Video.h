/*!
 * \ingroup Zarch
 *
 * \defgroup ZarchVideo Video
 */

#ifndef KXM_ZARCH_VIDEO_H_
#define KXM_ZARCH_VIDEO_H_

#include <memory>
#include <chrono>

#include <Game/ActorName.h>
#include <Game/ActorMap.h>
#include <Game/ReusableActors.h>
#include <Vectoid/Vector.h>
#include <Zarch/ActorInfo.h>
#include <Zarch/EventHandlerCore.h>
#include <Zarch/Events/ZarchEvent.h>
#include <Zarch/Video/Data.h>

namespace kxm {

namespace Game {
    template<class EventClass, class EventHandleClass> class EventLoop;
    class Actions;
}

namespace Zarch {

class ActorCreatedEvent;
class MoveEvent;
class VelocityEvent;
class ThrusterEvent;
class EventHandlerCore;
class ControlsState;

namespace Video {

class Lander;
class StarField;

//! Video subsystem for the <c>Zarch</c> game.
/*!
 *  \ingroup ZarchVideo
 */
class Video : public EventHandlerCore {
  public:
    Video(std::shared_ptr<Game::EventLoop<ZarchEvent, EventHandlerCore>> eventLoop);
    ~Video();
    //! Reconfigures the video system for the specified view port dimensions.
    void SetViewPort(int width, int height);
    void PrepareFrame(const ControlsState &controlsState);
    void Handle(const ActorCreatedEvent &event);
    void Handle(const MoveEvent &event);
    void Handle(const VelocityEvent &event);
    void Handle(const ThrusterEvent &event);
    void Handle(const FrameGeneratedEvent &event);
  
  private:
    Video(const Video &other);
    Video &operator=(const Video &other);
    
    std::shared_ptr<Game::EventLoop<ZarchEvent, EventHandlerCore>> eventLoop_;
    std::shared_ptr<Data>                                          data_;
    Game::ActorMap<ActorInfo>                                      actorMap_;
    std::shared_ptr<Game::Actions>                                 actions_;
    Game::ReusableActors<Lander>                                   landers_;
    Game::ActorName                                                landerName_;
    std::unique_ptr<StarField>                                     starField_;
    std::chrono::time_point<std::chrono::steady_clock>             lastFrameTime_;
};

}    // Namespace Video.
}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_VIDEO_H_
