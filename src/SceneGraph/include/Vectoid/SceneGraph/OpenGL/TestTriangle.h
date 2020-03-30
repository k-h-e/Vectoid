#ifndef VECTOID_SCENEGRAPH_OPENGL_TESTTRIANGLE_H_
#define VECTOID_SCENEGRAPH_OPENGL_TESTTRIANGLE_H_

#include <Vectoid/SceneGraph/TestTriangle.h>
#include <Vectoid/SceneGraph/OpenGL/OpenGL.h>

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

class RenderTarget;

//! Simple triangle geometry for testing purposes.
/*! 
 *  \ingroup VectoidOpenGL
 */ 
class TestTriangle : public Vectoid::SceneGraph::TestTriangle {
  public:
    friend class RenderTarget;
    
    TestTriangle(const TestTriangle &other) = delete;
    TestTriangle &operator=(const TestTriangle &other) = delete;
    void Render();
    
  private:
    TestTriangle();
  
    static const GLfloat vertices[9];
};

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_OPENGL_TESTTRIANGLE_H_
