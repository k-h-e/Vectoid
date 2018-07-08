#include <kxm/Zarch/Video/TerrainRenderer.h>

#include <kxm/Vectoid/Vector.h>

using namespace std;
using namespace kxm::Vectoid;

namespace kxm {
namespace Zarch {
namespace Video {

TerrainRenderer::TerrainRenderer(shared_ptr<Terrain> terrain,
                                 shared_ptr<MapParameters> mapParameters)
        : terrain_(terrain),
          mapParameters_(mapParameters),
          observerX_(0.0f),
          observerZ_(0.0f) {
    // Nop.
}

void TerrainRenderer::SetObserverPosition(const Vector &position) {
    observerX_ = position.x;
    observerZ_ = position.z;
}

void TerrainRenderer::GetObserverPosition(Vector *outPosition) {
    outPosition->x = observerX_;
    outPosition->z = observerZ_;
}

}    // Namespace Video.
}    // Namespace Zarch.
}    // Namespace kxm.
