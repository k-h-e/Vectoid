#ifndef VECTOID_SCENEGRAPH_VULKAN_TESTTRIANGLE_H_
#define VECTOID_SCENEGRAPH_VULKAN_TESTTRIANGLE_H_

#include <memory>
#include <Vectoid/SceneGraph/TestTriangle.h>

namespace Vectoid {
namespace SceneGraph {
namespace Vulkan {

class RenderTarget;
class Context;

//! Simple triangle geometry for testing purposes.
/*! 
 *  \ingroup VectoidVulkan
 */ 
class TestTriangle : public Vectoid::SceneGraph::TestTriangle {
  public:
    friend class RenderTarget;
    
    TestTriangle(const TestTriangle &other) = delete;
    TestTriangle &operator=(const TestTriangle &other) = delete;
    void Render();
    
  private:
    TestTriangle(const std::shared_ptr<Context> &context);
    
    std::shared_ptr<Context> context_;
};

}    // Namespace Vulkan.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_VULKAN_TESTTRIANGLE_H_

