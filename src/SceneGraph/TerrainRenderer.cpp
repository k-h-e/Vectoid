#include <Vectoid/SceneGraph/TerrainRenderer.h>

#include <Vectoid/Core/Vector.h>

using namespace std;
using namespace Vectoid::Core;

namespace Vectoid {
namespace SceneGraph {

TerrainRenderer::TerrainRenderer(const shared_ptr<Context> &context, const shared_ptr<Terrain> &terrain,
                                 const shared_ptr<MapParameters> &mapParameters)
        : Geometry(context),
          terrain_(terrain),
          mapParameters_(mapParameters),
          observerX_(0.0f),
          observerZ_(0.0f) {
    // Nop.
}

void TerrainRenderer::SetObserverPosition(const Vector<float> &position) {
    observerX_ = position.x;
    observerZ_ = position.z;
}

void TerrainRenderer::GetObserverPosition(Vector<float> *outPosition) {
    outPosition->x = observerX_;
    outPosition->z = observerZ_;
}

}    // Namespace SceneGraph.
}    // Namespace Vectoid.
