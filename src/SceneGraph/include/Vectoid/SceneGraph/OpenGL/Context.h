#ifndef VECTOID_SCENEGRAPH_OPENGL_CONTEXT_H_
#define VECTOID_SCENEGRAPH_OPENGL_CONTEXT_H_

#include <Vectoid/SceneGraph/Context.h>
#include <Vectoid/SceneGraph/OpenGL/OpenGL.h>

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
    ~Context();

    //! Initializes the <c>OpenGL</c> state to our definition of "neutral".
    /*!
     *  Interacts with the underlying graphics system (<c>OpenGL</c>).
     */
    void InitializeGL();
    //! Releases all <c>OpenGL</c> recourses currently maintained by all existing scene graph nodes.
    /*!
     *  Interacts with the underlying graphics system (<c>OpenGL</c>).
     */
    void ReleaseOpenGLResources();
    //! Releases all <c>OpenGL</c> resources currently registered with the context for release.
    /*!
     *  Interacts with the underlying graphics system (<c>OpenGL</c>).
     *
     *  \return
     *  Number of released <c>OpenGL</c> resources.
     */
    int ReleaseScheduledOpenGLResources();
    //! Used by scene graph nodes to ask the context object to release the specified VBO later at an appropriate time.
    /*!
     *  Does not interact with the underlying graphics system (<c>OpenGL</c>).
     */
    void ScheduleVBOForRelease(GLuint vbo, Node *node);
    //! Used by scene graph nodes to ask the context object to release the specified texture object later at an
    //! appropriate time.
    /*!
     *  Does not interact with the underlying graphics system (<c>OpenGL</c>).
     */
    void ScheduleTextureForRelease(GLuint texture, Node *node);

  private:
    std::vector<GLuint> vbosToRelease_;
    std::vector<GLuint> texturesToRelease_;
};

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_OPENGL_CONTEXT_H_
