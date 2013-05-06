//
//  NewVideo.h
//  kxm
//
//  Created by Kai Hergenröther on 4/28/13.
//
//


#ifndef KXM_ZARCH_VIDEO_H_
#define KXM_ZARCH_VIDEO_H_


#include <boost/shared_ptr.hpp>

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
        float                                             frameDeltaTimeS;
        boost::shared_ptr<Vectoid::PerspectiveProjection> projection;
        boost::shared_ptr<Vectoid::Camera>                camera;
        boost::shared_ptr<Vectoid::CoordSys>              landerCoordSys;
        Vectoid::Vector                                   landerVelocity;
        bool                                              landerThrusterEnabled;
        boost::shared_ptr<TerrainRenderer>                terrainRenderer;
        boost::shared_ptr<MapParameters>                  mapParameters;
        boost::shared_ptr<Terrain>                        terrain;
    };
    Video(boost::shared_ptr<Game::Processes<ZarchProcess::ProcessType> > processes);
    //! Reconfigures the video system for the specified view port dimensions.
    void SetViewPort(int width, int height);
    //! Renders a frame using the current scene graph state.
    void RenderFrame();
  
  private:
    Video(const Video &other);
    Video &operator=(const Video &other);
    //! (Re)implemented.
    void HandleEvent(const Game::Event &event);
    void HandleLanderMovedEvent(const PayloadEvent<Vectoid::Transform> &event);
    
    boost::shared_ptr<Game::Processes<ZarchProcess::ProcessType> > processes_;
    boost::shared_ptr<Data>                                        data_;
};

}    // Namespace Zarch.
}    // Namespace kxm.


#endif    // KXM_ZARCH_VIDEO_H_
