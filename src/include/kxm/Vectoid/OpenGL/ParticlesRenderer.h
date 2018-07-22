#ifndef KXM_VECTOID_OPENGL_PARTICLESRENDERER_H_
#define KXM_VECTOID_OPENGL_PARTICLESRENDERER_H_

#include <kxm/Vectoid/ParticlesRenderer.h>

#include <vector>
#include <kxm/Vectoid/OpenGL/OpenGL.h>

namespace kxm {
namespace Vectoid {
namespace OpenGL {

//! Renders particles.
/*!
 *  \ingroup VectoidOpenGL
 */
class ParticlesRenderer : public Vectoid::ParticlesRenderer {
  public:
    ParticlesRenderer(const std::shared_ptr<Vectoid::Particles> &particles);
    ParticlesRenderer(const ParticlesRenderer &other) = delete;
    ParticlesRenderer &operator=(const ParticlesRenderer &other) = delete;
    void Render();
    
  private:
    std::vector<GLfloat> vertexBuffer_;
};

}    // Namespace OpenGL.
}    // Namespace Vectoid.
}    // Namespace kxm.


#endif    // KXM_VECTOID_OPENGL_PARTICLESRENDERER_H_
