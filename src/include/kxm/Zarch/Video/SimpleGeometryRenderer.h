#ifndef KXM_ZARCH_VIDEO_SIMPLEGEOMETRYRENDERER_H_
#define KXM_ZARCH_VIDEO_SIMPLEGEOMETRYRENDERER_H_

#include <memory>
#include <kxm/Vectoid/GeometryInterface.h>

namespace kxm {
namespace Zarch {

class SimpleGeometry;

namespace Video {

//! Renders simple geometry.
/*!
 *  \ingroup ZarchVideo
 */
class SimpleGeometryRenderer : public virtual Vectoid::GeometryInterface {
  public:
    SimpleGeometryRenderer(const SimpleGeometryRenderer &other) = delete;
    SimpleGeometryRenderer &operator=(const SimpleGeometryRenderer &other) = delete;
    
  protected:
    SimpleGeometryRenderer(const std::shared_ptr<SimpleGeometry> &geometry);
    std::shared_ptr<SimpleGeometry> geometry_;
};

}    // Namespace Video.
}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_VIDEO_SIMPLEGEOMETRYRENDERER_H_
