#ifndef VECTOID_SCENEGRAPH_VULKAN_COORDSYS_H_
#define VECTOID_SCENEGRAPH_VULKAN_COORDSYS_H_

#include <Vectoid/SceneGraph/CoordSys.h>

namespace Vectoid {
namespace SceneGraph {
namespace Vulkan {

class RenderTarget;
class Context;

//! This scene graph node sets up a local coordinate system for its children.
/*! 
 *  \ingroup VectoidVulkan
 */ 
class CoordSys : public Vectoid::SceneGraph::CoordSys {
  public:
    friend class RenderTarget;
    
    CoordSys(const CoordSys &other) = delete;
    CoordSys &operator=(const CoordSys &other) = delete;
    void Render();

  private:
    CoordSys(const std::shared_ptr<Context> &context);
    
    std::shared_ptr<Context> context_;
};

}    // Namespace Vulkan.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_VULKAN_COORDSYS_H_
