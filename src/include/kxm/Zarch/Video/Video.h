/*!
 * \ingroup Zarch
 *
 * \defgroup ZarchVideo Video
 */

#ifndef KXM_ZARCH_VIDEO_VIDEO_H_
#define KXM_ZARCH_VIDEO_VIDEO_H_

#include <memory>
#include <chrono>

#include <kxm/Game/ActorName.h>
#include <kxm/Game/ActorMap.h>
#include <kxm/Game/ReusableActors.h>
#include <kxm/Vectoid/Vector.h>
#include <kxm/Zarch/ActorInfo.h>
#include <kxm/Zarch/EventHandlerCore.h>
#include <kxm/Zarch/Events/ZarchEvent.h>
#include <kxm/Zarch/Video/Data.h>

namespace kxm {

namespace Game {
    template<class EventClass, class EventHandleClass> class EventLoop;
    class Actions;
}

namespace Zarch {

class ActorCreationEvent;
class ActorTerminationEvent;
class ControlsEvent;
class MoveEvent;
class VelocityEvent;
class EventHandlerCore;
class ControlsState;
class TriggerEvent;

namespace Video {

class Actor;
class Lander;
class Shot;
class Saucer;
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
    void Handle(const ActorCreationEvent &event);
    void Handle(const ActorTerminationEvent &event);
    void Handle(const ControlsEvent &event);
    void Handle(const MoveEvent &event);
    void Handle(const VelocityEvent &event);
    void Handle(const TriggerEvent &event);
  
  private:
    Video(const Video &other);
    Video &operator=(const Video &other);
    
    std::shared_ptr<Game::EventLoop<ZarchEvent, EventHandlerCore>> eventLoop_;
    std::shared_ptr<Data>                                          data_;
    Game::ActorMap<ActorInfo<Actor>>                               actorMap_;
    std::shared_ptr<Game::Actions>                                 actions_;
    Game::ReusableActors<Lander>                                   landers_;
    Game::ReusableActors<Shot>                                     shots_;
    Game::ReusableActors<Saucer>                                   saucers_;
    std::unique_ptr<StarField>                                     starField_;
    std::chrono::time_point<std::chrono::steady_clock>             lastFrameTime_;
    bool                                                           thruster_,
                                                                   trigger_;
};

}    // Namespace Video.
}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_VIDEO_VIDEO_H_
