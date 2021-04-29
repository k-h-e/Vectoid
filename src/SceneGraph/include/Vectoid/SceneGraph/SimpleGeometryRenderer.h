#ifndef VECTOID_SCENEGRAPH_SIMPLEGEOMETRYRENDERER_H_
#define VECTOID_SCENEGRAPH_SIMPLEGEOMETRYRENDERER_H_

#include <memory>
#include <Vectoid/SceneGraph/GeometryInterface.h>

namespace Vectoid {
namespace SceneGraph {

class SimpleGeometry;

//! Renders simple geometry.
class SimpleGeometryRenderer : public virtual Vectoid::SceneGraph::GeometryInterface {
  public:
    SimpleGeometryRenderer(const SimpleGeometryRenderer &other) = delete;
    SimpleGeometryRenderer &operator=(const SimpleGeometryRenderer &other) = delete;
    
  protected:
    SimpleGeometryRenderer(const std::shared_ptr<SimpleGeometry> &geometry);
    std::shared_ptr<SimpleGeometry> geometry_;
};

}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_SIMPLEGEOMETRYRENDERER_H_
