#ifndef VECTOID_SCENEGRAPH_OPENGL_SIMPLELIGHTING_H_
#define VECTOID_SCENEGRAPH_OPENGL_SIMPLELIGHTING_H_

#include <Vectoid/SceneGraph/SimpleLighting.h>

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

class Context;
class RenderTarget;

//! Simple lighting setup using one light source.
class SimpleLighting : public Vectoid::SceneGraph::SimpleLighting {
  public:
    SimpleLighting()                                        = delete;
    SimpleLighting(const std::shared_ptr<Context> &context);
    SimpleLighting(const SimpleLighting &other)             = delete;
    SimpleLighting &operator=(const SimpleLighting &other)  = delete;
    SimpleLighting(SimpleLighting &&other)                  = delete;
    SimpleLighting &operator=(SimpleLighting &&other)       = delete;

    void RenderPre() override;
};

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_OPENGL_SIMPLELIGHTING_H_
