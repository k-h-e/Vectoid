#ifndef KXM_VECTOID_METAL_TESTTRIANGLE_H_
#define KXM_VECTOID_METAL_TESTTRIANGLE_H_

#include <memory>
#include <kxm/Vectoid/TestTriangle.h>

namespace kxm {
namespace Vectoid {
namespace Metal {

class Context;

//! Simple triangle geometry for testing purposes.
/*! 
 *  \ingroup VectoidMetal
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

}    // Namespace Metal.
}    // Namespace Vectoid.
}    // Namespace kxm.

#endif    // KXM_VECTOID_METAL_TESTTRIANGLE_H_

