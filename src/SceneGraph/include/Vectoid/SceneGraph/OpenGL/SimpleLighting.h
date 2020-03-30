#ifndef VECTOID_SCENEGRAPH_OPENGL_SIMPLELIGHTING_H_
#define VECTOID_SCENEGRAPH_OPENGL_SIMPLELIGHTING_H_

#include <Vectoid/SceneGraph/SimpleLighting.h>

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

//! Simple lighting setup using one light source.
/*!
 *  \ingroup Vectoid
 */
class SimpleLighting : public Vectoid::SceneGraph::SimpleLighting {
  public:
    SimpleLighting();
    SimpleLighting(const SimpleLighting &other)             = delete;
    SimpleLighting &operator=(const SimpleLighting &other)  = delete;
    SimpleLighting(const SimpleLighting &&other)            = delete;
    SimpleLighting &operator=(const SimpleLighting &&other) = delete;
    virtual void Render();
};

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_OPENGL_SIMPLELIGHTING_H_
