/*!
 * \ingroup Zarch
 *
 * \defgroup ZarchVideo Video
 */

#ifndef KXM_ZARCH_VIDEO_H_
#define KXM_ZARCH_VIDEO_H_

#include <memory>

#include <Game/ProcessOwnerInterface.h>
#include <Game/Actors.h>
#include <Vectoid/Vector.h>
#include <Zarch/EventHandlerCore.h>
#include <Zarch/Events/ZarchEvent.h>
#include <Zarch/Video/Lander.h>

namespace kxm {

namespace Game {
    template<class EventClass, class EventHandleClass> class EventLoop;
}

namespace Vectoid {
    class PerspectiveProjection;
    class Camera;
    class CoordSys;
}

namespace Zarch {

class MapParameters;
class Terrain;
class ActorCreatedEvent;
class FrameTimeEvent;
class LanderMoveEvent;
class LanderVelocityEvent;
class LanderThrusterEvent;

namespace Video {

class TerrainRenderer;
class CameraProcess;
class StarFieldProcess;
class ThrusterParticlesProcess;

//! Video subsystem for the <c>Zarch</c> game.
/*!
 *  \ingroup ZarchVideo
 */
class Video : public EventHandlerCore,
              public virtual Game::ProcessOwnerInterface {
  public:
    struct Data {
        Data() : frameDeltaTimeS(0.0f),
                 landerThrusterEnabled(false) {}
        float                                           frameDeltaTimeS;
        std::shared_ptr<Vectoid::PerspectiveProjection> projection;
        std::shared_ptr<Vectoid::Camera>                camera;
        std::shared_ptr<Vectoid::CoordSys>              landerCoordSys;
        Vectoid::Vector                                 landerVelocity;
        bool                                            landerThrusterEnabled;
        std::shared_ptr<TerrainRenderer>                terrainRenderer;
        std::shared_ptr<MapParameters>                  mapParameters;
        std::shared_ptr<Terrain>                        terrain;
    };
    Video(std::shared_ptr<Game::EventLoop<ZarchEvent, EventHandlerCore>> eventLoop);
    ~Video();
    //! Reconfigures the video system for the specified view port dimensions.
    void SetViewPort(int width, int height);
    void HandleProcessFinished(Game::ProcessInterface *process);
    void Handle(const ActorCreatedEvent &event);
    void Handle(const FrameTimeEvent &event);
    void Handle(const FrameGeneratedEvent &event);
    void Handle(const LanderMoveEvent &event);
    void Handle(const LanderVelocityEvent &event);
    void Handle(const LanderThrusterEvent &event);
  
  private:
    Video(const Video &other);
    Video &operator=(const Video &other);
    
    std::shared_ptr<Game::EventLoop<ZarchEvent, EventHandlerCore>> eventLoop_;
    std::shared_ptr<Data>                                          data_;
    std::unique_ptr<CameraProcess>                                 cameraProcess_;
    std::unique_ptr<StarFieldProcess>                              starFieldProcess_;
    std::unique_ptr<ThrusterParticlesProcess>                      thrusterParticlesProcess_;
    Game::Actors<void>                                             actors_;
    Lander                                                         lander_;
    bool                                                           landerInUse_;
};

}    // Namespace Video.
}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_VIDEO_H_
