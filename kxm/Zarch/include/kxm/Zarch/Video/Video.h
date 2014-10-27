//
//  NewVideo.h
//  kxm
//
//  Created by Kai Hergenröther on 4/28/13.
//
//


#ifndef KXM_ZARCH_VIDEO_H_
#define KXM_ZARCH_VIDEO_H_


#include <memory>

#include <kxm/Game/EventHandlerInterface.h>
#include <kxm/Zarch/processes.h>


namespace kxm {

namespace Game {
    template<class T> class Processes;
}

namespace Vectoid {
    class PerspectiveProjection;
    class Camera;
    class CoordSys;
}

namespace Zarch {

class TerrainRenderer;
class MapParameters;
class Terrain;

//! Video subsystem for the <c>Zarch</c> game.
/*!
 *  \ingroup Zarch
 */
class Video : public virtual Game::EventHandlerInterface {
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
    Video(std::shared_ptr<Game::Processes<ZarchProcess::ProcessType>> processes);
    //! Reconfigures the video system for the specified view port dimensions.
    void SetViewPort(int width, int height);
    //! Renders a frame using the current scene graph state.
    void RenderFrame();
  
  private:
    Video(const Video &other);
    Video &operator=(const Video &other);
    //! (Re)implemented.
    void HandleEvent(const Game::Event &event);
    void HandleLanderMovedEvent(const Event<Vectoid::Transform> &event);
    
    std::shared_ptr<Game::Processes<ZarchProcess::ProcessType>> processes_;
    std::shared_ptr<Data>                                        data_;
};

}    // Namespace Zarch.
}    // Namespace kxm.


#endif    // KXM_ZARCH_VIDEO_H_
