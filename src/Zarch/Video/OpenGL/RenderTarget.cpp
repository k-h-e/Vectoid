#include <kxm/Zarch/Video/OpenGL/RenderTarget.h>

#include <kxm/Zarch/Video/OpenGL/SimpleGeometryRenderer.h>
#include <kxm/Zarch/Video/OpenGL/TerrainRenderer.h>

using std::shared_ptr;

namespace kxm {
namespace Zarch {
namespace Video {
namespace OpenGL {

RenderTarget::RenderTarget()
        : Vectoid::OpenGL::RenderTarget() {
    // Nop.
}

shared_ptr<Video::SimpleGeometryRenderer> RenderTarget::NewSimpleGeometryRenderer(
        const shared_ptr<SimpleGeometry> &geometry) {
    return std::make_shared<SimpleGeometryRenderer>(geometry);
}

shared_ptr<Video::TerrainRenderer> RenderTarget::NewTerrainRenderer(
        const shared_ptr<Terrain> &terrain, const shared_ptr<MapParameters> &mapParameters) {
    return std::make_shared<TerrainRenderer>(terrain, mapParameters);
}

}    // Namespace OpenGL.
}    // Namespace Video.
}    // Namespace Zarch.
}    // Namespace kxm.

