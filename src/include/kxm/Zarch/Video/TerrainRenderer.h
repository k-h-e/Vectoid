#ifndef KXM_ZARCH_VIDEO_TERRAINRENDERER_H_
#define KXM_ZARCH_VIDEO_TERRAINRENDERER_H_

#include <vector>
#include <memory>
#include <kxm/Vectoid/GeometryInterface.h>

namespace kxm {

namespace Vectoid {
    class Vector;
}

namespace Zarch {

class Terrain;
class MapParameters;

namespace Video {

//! Renders the terrain.
/*!
 *  \ingroup ZarchVideo
 */
class TerrainRenderer : public virtual Vectoid::GeometryInterface {
  public:
    TerrainRenderer(const std::shared_ptr<Terrain> &terrain,
                    const std::shared_ptr<MapParameters> &mapParameters);
    TerrainRenderer(const TerrainRenderer &other) = delete;
    TerrainRenderer &operator=(const TerrainRenderer &other) = delete;
    //! Sets the observer's position in the <c>xz</c>-plane, ignoring the <c>y</c>-coordinate.
    void SetObserverPosition(const Vectoid::Vector &position);
    //! Gets the observer's position in the <c>xz</c>-plane, not affecting the output vector's <c>y</c>-coordinate.
    void GetObserverPosition(Vectoid::Vector *outPosition);
    
  protected:
    std::shared_ptr<Terrain>             terrain_;
    std::shared_ptr<const MapParameters> mapParameters_;
    float                                observerX_, observerZ_;
};

}    // Namespace Video.
}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_VIDEO_TERRAINRENDERER_H_
