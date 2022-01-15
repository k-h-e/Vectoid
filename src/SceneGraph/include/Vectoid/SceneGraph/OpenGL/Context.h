#ifndef VECTOID_SCENEGRAPH_OPENGL_CONTEXT_H_
#define VECTOID_SCENEGRAPH_OPENGL_CONTEXT_H_

#include <Vectoid/SceneGraph/Context.h>

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

//! Holds context information for the <c>OpenGL</c> renderer.
class Context : public SceneGraph::Context {
  public:
    Context();
    Context(const Context &other)            = delete;
    Context &operator=(const Context &other) = delete;
    Context(Context &&other)                 = delete;
    Context &operator=(Context &&other)      = delete;
};

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_OPENGL_CONTEXT_H_
