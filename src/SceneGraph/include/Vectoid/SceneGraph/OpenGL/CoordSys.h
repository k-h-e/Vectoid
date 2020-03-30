#ifndef VECTOID_SCENEGRAPH_OPENGL_COORDSYS_H_
#define VECTOID_SCENEGRAPH_OPENGL_COORDSYS_H_

#include <Vectoid/SceneGraph/CoordSys.h>

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

class RenderTarget;

//! This scene graph node sets up a local coordinate system for its children.
/*! 
 *  \ingroup VectoidOpenGL
 */ 
class CoordSys : public Vectoid::SceneGraph::CoordSys {
  public:
    friend class RenderTarget;
    
    CoordSys(const CoordSys &other) = delete;
    CoordSys &operator=(const CoordSys &other) = delete;
    void Render();
    
  private:
    CoordSys();
};

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_OPENGL_COORDSYS_H_
