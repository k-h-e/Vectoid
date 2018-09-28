#ifndef KXM_VECTOID_VULKAN_TESTTRIANGLE_H_
#define KXM_VECTOID_VULKAN_TESTTRIANGLE_H_

#include <memory>
#include <kxm/Vectoid/TestTriangle.h>

namespace kxm {
namespace Vectoid {
namespace Vulkan {

class Context;

//! Simple triangle geometry for testing purposes.
/*! 
 *  \ingroup VectoidVulkan
 */ 
class TestTriangle : public Vectoid::TestTriangle {
  public:
    TestTriangle(const std::shared_ptr<Context> &context);   
    TestTriangle(const TestTriangle &other) = delete;
    TestTriangle &operator=(const TestTriangle &other) = delete;
    void Render();
    
  private:
    std::shared_ptr<Context> context_;
};

}    // Namespace Vulkan.
}    // Namespace Vectoid.
}    // Namespace kxm.

#endif    // KXM_VECTOID_VULKAN_TESTTRIANGLE_H__

