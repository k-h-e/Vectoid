#include <kxm/Zarch/Video/Vulkan/RenderTarget.h>

#include <kxm/Zarch/Video/Vulkan/SimpleGeometryRenderer.h>
#include <kxm/Zarch/Video/Vulkan/TerrainRenderer.h>

using namespace std;

namespace kxm {
namespace Zarch {
namespace Video {
namespace Vulkan {

RenderTarget::RenderTarget()
        : Vectoid::Vulkan::RenderTarget() {

}

shared_ptr<Video::SimpleGeometryRenderer> RenderTarget::NewSimpleGeometryRenderer(
        const shared_ptr<SimpleGeometry> &geometry) {
    return shared_ptr<SimpleGeometryRenderer>(new SimpleGeometryRenderer(context_, geometry));
}

shared_ptr<Video::TerrainRenderer> RenderTarget::NewTerrainRenderer(const shared_ptr<Terrain> &terrain,
                                                                    const shared_ptr<MapParameters> &mapParameters) {
    return shared_ptr<TerrainRenderer>(new TerrainRenderer(context_, terrain, mapParameters));
}

}    // Namespace Vulkan.
}    // Namespace Video.
}    // Namespace Zarch.
}    // Namespace kxm.

