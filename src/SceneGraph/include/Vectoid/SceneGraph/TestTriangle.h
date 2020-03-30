#ifndef VECTOID_SCENEGRAPH_TESTTRIANGLE_H_
#define VECTOID_SCENEGRAPH_TESTTRIANGLE_H_

#include <Vectoid/SceneGraph/GeometryInterface.h>

namespace Vectoid {
namespace SceneGraph {

//! Simple triangle geometry for testing purposes.
/*! 
 *  \ingroup Vectoid
 */ 
class TestTriangle : public virtual GeometryInterface {
  public:
    TestTriangle(const TestTriangle &other) = delete;
    TestTriangle &operator=(const TestTriangle &other) = delete;
    
  protected:
    TestTriangle() {}
};

}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_TESTTRIANGLE_H_
