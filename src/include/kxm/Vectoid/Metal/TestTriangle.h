#ifndef KXM_VECTOID_METAL_TESTTRIANGLE_H_
#define KXM_VECTOID_METAL_TESTTRIANGLE_H_

#include <kxm/Vectoid/TestTriangle.h>

namespace kxm {
namespace Vectoid {
namespace Metal {

//! Simple triangle geometry for testing purposes.
/*! 
 *  \ingroup VectoidMetal
 */ 
class TestTriangle : public Vectoid::TestTriangle {
  public:
    TestTriangle();   
    TestTriangle(const TestTriangle &other) = delete;
    TestTriangle &operator=(const TestTriangle &other) = delete;
    void Render();
};

}    // Namespace Metal.
}    // Namespace Vectoid.
}    // Namespace kxm.

#endif    // KXM_VECTOID_METAL_TESTTRIANGLE_H_

