#ifndef KXM_VECTOID_OPENGL_COORDSYS_H_
#define KXM_VECTOID_OPENGL_COORDSYS_H_

#include <kxm/Vectoid/CoordSys.h>

namespace kxm {
namespace Vectoid {
namespace OpenGL {

//! This scene graph node sets up a local coordinate system for its children.
/*! 
 *  \ingroup VectoidOpenGL
 */ 
class CoordSys : public Vectoid::CoordSys {
  public:
    CoordSys();
    CoordSys(const CoordSys &other) = delete;
    CoordSys &operator=(const CoordSys &other) = delete;
    void Render(RenderContext *context);
};

}    // Namespace OpenGL.
}    // Namespace Vectoid.
}    // Namespace kxm.

#endif    // KXM_VECTOID_OPENGL_COORDSYS_H_
