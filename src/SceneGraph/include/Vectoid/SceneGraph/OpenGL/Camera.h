#ifndef VECTOID_SCENEGRAPH_OPENGL_CAMERA_H_
#define VECTOID_SCENEGRAPH_OPENGL_CAMERA_H_

#include <Vectoid/SceneGraph/Camera.h>

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

class RenderTarget;

//! This scene graph node represents a camera.
/*! 
 *  \ingroup VectoidOpenGL
 */ 
class Camera : public Vectoid::SceneGraph::Camera {
  public:
    friend class RenderTarget;
    
    Camera(const Camera &other) = delete;
    Camera &operator=(const Camera &other) = delete;
    void Render();
    
  private:
    Camera();
};

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_OPENGL_CAMERA_H_