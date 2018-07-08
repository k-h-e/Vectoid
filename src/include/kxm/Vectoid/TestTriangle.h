#ifndef KXM_VECTOID_TESTTRIANGLE_H_
#define KXM_VECTOID_TESTTRIANGLE_H_

#include <kxm/Vectoid/GeometryInterface.h>

namespace kxm {
namespace Vectoid {

//! Simple triangle geometry for testing purposes.
/*! 
 *  \ingroup Vectoid
 */ 
class TestTriangle : public virtual GeometryInterface {
  public:
    TestTriangle() {}
    TestTriangle(const TestTriangle &other) = delete;
    TestTriangle &operator=(const TestTriangle &other) = delete;
};

}    // Namespace Vectoid.
}    // Namespace kxm.

#endif    // KXM_VECTOID_TESTTRIANGLE_H_
