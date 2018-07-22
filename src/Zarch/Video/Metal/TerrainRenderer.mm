#include <kxm/Zarch/Video/Metal/TerrainRenderer.h>

#include <kxm/Core/IntModN.h>
#include <kxm/Zarch/Terrain.h>
#include <kxm/Zarch/MapParameters.h>

using namespace std;

namespace kxm {
namespace Zarch {
namespace Video {
namespace Metal {

TerrainRenderer::TerrainRenderer(const shared_ptr<Vectoid::Metal::Context> &context, const shared_ptr<Terrain> &terrain,
                                 const shared_ptr<MapParameters> &mapParameters)
        : Video::TerrainRenderer(terrain, mapParameters),
          context_(context) {

}

void TerrainRenderer::Render() {
   
}

}    // Namespace Metal.
}    // Namespace Video.
}    // Namespace Zarch.
}    // Namespace kxm.
