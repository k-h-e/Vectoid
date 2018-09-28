#ifndef KXM_VECTOID_OPENGL_GEODE_H_
#define KXM_VECTOID_OPENGL_GEODE_H_

#include <kxm/Vectoid/Geode.h>

namespace kxm {
namespace Vectoid {
namespace OpenGL {

class RenderTarget;

//! This scene graph node represents actual geometry in the scene (geode = geometry node).
/*! 
 *  \ingroup VectoidOpenGL
 */
class Geode : public Vectoid::Geode {
  public:
    friend class RenderTarget;
    
    Geode(const Geode &other) = delete;
    Geode &operator=(const Geode &other) = delete;
    
  private:
    Geode(const std::shared_ptr<GeometryInterface> &geometry);
};

}    // Namespace OpenGL.
}    // Namespace Vectoid.
}    // Namespace kxm.


#endif    // KXM_VECTOID_OPENGL_GEODE_H_
