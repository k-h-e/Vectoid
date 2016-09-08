/*!
 * \ingroup Zarch
 *
 * \defgroup ZarchVideo Video
 */

#ifndef KXM_ZARCH_VIDEO_DATA_H_
#define KXM_ZARCH_VIDEO_DATA_H_

#include <memory>

#include <Game/ProcessOwnerInterface.h>
#include <Game/Actors.h>
#include <Vectoid/Vector.h>
#include <Zarch/EventHandlerCore.h>
#include <Zarch/Events/ZarchEvent.h>
#include <Zarch/Video/Lander.h>

namespace kxm {

namespace Vectoid {
    class PerspectiveProjection;
    class Camera;
    class CoordSys;
}

namespace Zarch {

class MapParameters;
class Terrain;

namespace Video {

class TerrainRenderer;

//! Holds together common data the video sub system's components work on.
/*!
 *  \ingroup ZarchVideo
 */
struct Data {
    Data() : frameDeltaTimeS(0.0f),
             landerThrusterEnabled(false) {}
    float                                           frameDeltaTimeS;
    std::shared_ptr<Vectoid::PerspectiveProjection> projection;
    std::shared_ptr<Vectoid::Camera>                camera;
    Vectoid::Vector                                 landerVelocity;
    bool                                            landerThrusterEnabled;
    std::shared_ptr<TerrainRenderer>                terrainRenderer;
    std::shared_ptr<MapParameters>                  mapParameters;
    std::shared_ptr<Terrain>                        terrain;
};

}    // Namespace Video.
}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_VIDEO_DATA_H_