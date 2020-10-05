#ifndef VECTOID_SCENEGRAPH_OPENGL_PARTICLESRENDERER_H_
#define VECTOID_SCENEGRAPH_OPENGL_PARTICLESRENDERER_H_

#include <Vectoid/SceneGraph/ParticlesRenderer.h>

#include <vector>
#include <Vectoid/SceneGraph/OpenGL/OpenGL.h>

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

class RenderTarget;

//! Renders particles.
class ParticlesRenderer : public Vectoid::SceneGraph::ParticlesRenderer {
  public:
    friend class RenderTarget;
    
    ParticlesRenderer(const ParticlesRenderer &other) = delete;
    ParticlesRenderer &operator=(const ParticlesRenderer &other) = delete;
    void Render();
    
  private:
    ParticlesRenderer(const std::shared_ptr<Core::Particles> &particles);
    
    std::vector<GLfloat> vertexBuffer_;
};

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_OPENGL_PARTICLESRENDERER_H_
