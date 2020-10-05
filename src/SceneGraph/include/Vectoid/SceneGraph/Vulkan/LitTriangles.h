#ifndef VECTOID_SCENEGRAPH_VULKAN_LITTRIANGLES_H_
#define VECTOID_SCENEGRAPH_VULKAN_LITTRIANGLES_H_

#include <Vectoid/SceneGraph/LitTriangles.h>

namespace Vectoid {
namespace SceneGraph {
namespace Vulkan {

//! Renders lit triangles.
class LitTriangles : public Vectoid::SceneGraph::LitTriangles {
  public:
    LitTriangles(const std::shared_ptr<Core::TriangleProviderInterface> &triangleProvider);
    LitTriangles(const LitTriangles &other)            = delete;
    LitTriangles &operator=(const LitTriangles &other) = delete;
    LitTriangles(LitTriangles &&other)                 = delete;
    LitTriangles &operator=(LitTriangles &&other)      = delete;
    virtual void Render();
};

}    // Namespace Vulkan.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_VULKAN_LITTRIANGLES_H_
