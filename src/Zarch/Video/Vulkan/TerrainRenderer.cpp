#include <kxm/Zarch/Video/Vulkan/TerrainRenderer.h>

#include <kxm/Core/IntModN.h>
#include <kxm/Zarch/Terrain.h>
#include <kxm/Zarch/MapParameters.h>

using namespace std;

namespace kxm {
namespace Zarch {
namespace Video {
namespace Vulkan {

TerrainRenderer::TerrainRenderer(const shared_ptr<Vectoid::Vulkan::Context> &context,
                                 const shared_ptr<Terrain> &terrain, const shared_ptr<MapParameters> &mapParameters)
        : Video::TerrainRenderer(terrain, mapParameters),
          context_(context) {

}

void TerrainRenderer::Render() {
   
}

}    // Namespace Vulkan.
}    // Namespace Video.
}    // Namespace Zarch.
}    // Namespace kxm.
