#ifndef KXM_VECTOID_OPENGL_TESTTRIANGLE_H_
#define KXM_VECTOID_OPENGL_TESTTRIANGLE_H_

#include <kxm/Vectoid/TestTriangle.h>

#include <kxm/Vectoid/OpenGL/OpenGL.h>

namespace kxm {
namespace Vectoid {
namespace OpenGL {

//! Simple triangle geometry for testing purposes.
/*! 
 *  \ingroup VectoidOpenGL
 */ 
class TestTriangle : public Vectoid::TestTriangle {
  public:
    TestTriangle(const TestTriangle &other) = delete;
    TestTriangle &operator=(const TestTriangle &other) = delete;
    void Render(RenderContext *context);
    
  private:
    static const GLfloat vertices[9];
};

}    // Namespace OpenGL.
}    // Namespace Vectoid.
}    // Namespace kxm.

#endif    // KXM_VECTOID_OPENGL_TESTTRIANGLE_H_
