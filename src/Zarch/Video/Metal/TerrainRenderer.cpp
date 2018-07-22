#include <kxm/Zarch/Video/Metal/TerrainRenderer.h>

#include <kxm/Core/IntModN.h>
#include <kxm/Zarch/Terrain.h>
#include <kxm/Zarch/MapParameters.h>

using namespace std;

namespace kxm {
namespace Zarch {
namespace Video {
namespace Metal {

TerrainRenderer::TerrainRenderer(shared_ptr<Terrain> terrain,
                                 shared_ptr<MapParameters> mapParameters)
        : Video::TerrainRenderer(terrain, mapParameters) {

}

void TerrainRenderer::Render() {
   
}

}    // Namespace Metal.
}    // Namespace Video.
}    // Namespace Zarch.
}    // Namespace kxm.
