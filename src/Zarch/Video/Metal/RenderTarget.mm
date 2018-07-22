#include <kxm/Zarch/Video/Metal/RenderTarget.h>

#include <kxm/Zarch/Video/Metal/SimpleGeometryRenderer.h>
#include <kxm/Zarch/Video/Metal/TerrainRenderer.h>

using std::shared_ptr;

namespace kxm {
namespace Zarch {
namespace Video {
namespace Metal {

RenderTarget::RenderTarget(MTKView *metalView)
        : Vectoid::Metal::RenderTarget(metalView) {

}

shared_ptr<Video::SimpleGeometryRenderer> RenderTarget::NewSimpleGeometryRenderer(
        const shared_ptr<SimpleGeometry> &geometry) {
    return std::make_shared<SimpleGeometryRenderer>(context_, geometry);
}

shared_ptr<Video::TerrainRenderer> RenderTarget::NewTerrainRenderer(const shared_ptr<Terrain> &terrain,
                                                                    const shared_ptr<MapParameters> &mapParameters) {
    return std::make_shared<TerrainRenderer>(context_, terrain, mapParameters);
}

}    // Namespace Metal.
}    // Namespace Video.
}    // Namespace Zarch.
}    // Namespace kxm.

