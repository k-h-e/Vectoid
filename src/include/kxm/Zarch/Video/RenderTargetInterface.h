#ifndef KXM_ZARCH_VIDEO_RENDERTARGETINTERFACE_H_
#define KXM_ZARCH_VIDEO_RENDERTARGETINTERFACE_H_

#include <kxm/Vectoid/RenderTargetInterface.h>

namespace kxm {
namespace Zarch {

class MapParameters;
class SimpleGeometry;
class Terrain;

namespace Video {


class SimpleGeometryRenderer;
class TerrainRenderer;

//! Render target interface, extended to include Zarch-specific graphics resources.
/*!
 *  \ingroup ZarchVideo
 */
class RenderTargetInterface : public virtual Vectoid::RenderTargetInterface {
  public:
    virtual std::shared_ptr<SimpleGeometryRenderer> NewSimpleGeometryRenderer(
        const std::shared_ptr<SimpleGeometry> &geometry) = 0;
    virtual std::shared_ptr<TerrainRenderer> NewTerrainRenderer(std::shared_ptr<Terrain> terrain,
                                                                std::shared_ptr<MapParameters> mapParameters) = 0;
};

}    // Namespace Video.
}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_VIDEO_RENDERTARGETINTERFACE_H_
