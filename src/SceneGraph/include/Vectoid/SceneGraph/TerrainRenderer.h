#ifndef VECTOID_SCENEGRAPH_TERRAINRENDERER_H_
#define VECTOID_SCENEGRAPH_TERRAINRENDERER_H_

#include <vector>
#include <memory>
#include <Vectoid/SceneGraph/GeometryInterface.h>

namespace Vectoid {

namespace Core {
    template<typename T> class Vector;
}

namespace SceneGraph {

class Terrain;
class MapParameters;

//! Renders the terrain.
class TerrainRenderer : public virtual Vectoid::SceneGraph::GeometryInterface {
  public:
    TerrainRenderer(const TerrainRenderer &other) = delete;
    TerrainRenderer &operator=(const TerrainRenderer &other) = delete;
    //! Sets the observer's position in the <c>xz</c>-plane, ignoring the <c>y</c>-coordinate.
    void SetObserverPosition(const Vectoid::Core::Vector<float> &position);
    //! Gets the observer's position in the <c>xz</c>-plane, not affecting the output vector's <c>y</c>-coordinate.
    void GetObserverPosition(Vectoid::Core::Vector<float> *outPosition);
    
  protected:
    TerrainRenderer(const std::shared_ptr<Terrain> &terrain,
                    const std::shared_ptr<MapParameters> &mapParameters);

    std::shared_ptr<Terrain>             terrain_;
    std::shared_ptr<const MapParameters> mapParameters_;
    float                                observerX_, observerZ_;
};

}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_TERRAINRENDERER_H_
