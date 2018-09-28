#include <kxm/Zarch/Video/OpenGL/RenderTarget.h>

#include <kxm/Zarch/Video/OpenGL/SimpleGeometryRenderer.h>
#include <kxm/Zarch/Video/OpenGL/TerrainRenderer.h>

using namespace std;

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
    return shared_ptr<SimpleGeometryRenderer>(new SimpleGeometryRenderer(geometry));
}

shared_ptr<Video::TerrainRenderer> RenderTarget::NewTerrainRenderer(
        const shared_ptr<Terrain> &terrain, const shared_ptr<MapParameters> &mapParameters) {
    return shared_ptr<TerrainRenderer>(new TerrainRenderer(terrain, mapParameters));
}

}    // Namespace OpenGL.
}    // Namespace Video.
}    // Namespace Zarch.
}    // Namespace kxm.

