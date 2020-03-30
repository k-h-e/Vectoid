#ifndef VECTOID_SCENEGRAPH_OPENGL_GEODE_H_
#define VECTOID_SCENEGRAPH_OPENGL_GEODE_H_

#include <Vectoid/SceneGraph/Geode.h>

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

class RenderTarget;

//! This scene graph node represents actual geometry in the scene (geode = geometry node).
/*! 
 *  \ingroup VectoidOpenGL
 */
class Geode : public Vectoid::SceneGraph::Geode {
  public:
    friend class RenderTarget;
    
    Geode(const Geode &other) = delete;
    Geode &operator=(const Geode &other) = delete;
    
  private:
    Geode(const std::shared_ptr<GeometryInterface> &geometry);
};

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.


#endif    // VECTOID_SCENEGRAPH_OPENGL_GEODE_H_
