/*!
 * \ingroup Zarch
 *
 * \defgroup ZarchVideo Video
 * \brief Zarch's video subsystem.
 */

#ifndef KXM_ZARCH_VIDEO_DATA_H_
#define KXM_ZARCH_VIDEO_DATA_H_

#include <memory>

#include <kxm/Vectoid/Vector.h>
#include <kxm/Game/ActorName.h>
#include <kxm/Zarch/EventHandlerCore.h>
#include <kxm/Zarch/Events/ZarchEvent.h>
#include <kxm/Zarch/Video/Lander.h>

namespace kxm {

namespace Vectoid {
    class PerspectiveProjection;
    class Camera;
    class CoordSys;
    class Particles;
    class TextConsole;
}

namespace Zarch {

class MapParameters;
class Terrain;

namespace Video {

class RenderTargetInterface;
class TerrainRenderer;

//! Holds together common data the video sub system's components work on.
/*!
 *  \ingroup ZarchVideo
 */
struct Data {
    float                                           frameDeltaTimeS;
    Game::ActorName                                 focusLander;
    std::shared_ptr<Vectoid::PerspectiveProjection> projection;
    std::shared_ptr<Vectoid::Camera>                camera;
    std::shared_ptr<Vectoid::Particles>             shotParticles,
                                                    thrusterParticles;
    std::shared_ptr<Vectoid::TextConsole>           statsConsole;
    std::shared_ptr<Vectoid::CoordSys>              statsConsoleCoordSys;
    std::shared_ptr<TerrainRenderer>                terrainRenderer;
    std::shared_ptr<MapParameters>                  mapParameters;
    std::shared_ptr<Terrain>                        terrain;
    Vectoid::Vector                                 statsConsolePosition;
    std::shared_ptr<RenderTargetInterface>          renderTarget;
    
    Data() : frameDeltaTimeS(0.0f) {}
    void StartParticleExplosion(const Vectoid::Vector &position, int particleCount);
};

}    // Namespace Video.
}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_VIDEO_DATA_H_
