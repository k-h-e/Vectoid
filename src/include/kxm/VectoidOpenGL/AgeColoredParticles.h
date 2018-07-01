#ifndef KXM_VECTOID_OPENGL_AGECOLOREDPARTICLES_H_
#define KXM_VECTOID_OPENGL_AGECOLOREDPARTICLES_H_

#include <kxm/Vectoid/AgeColoredParticles.h>

namespace kxm {
namespace Vectoid {
namespace OpenGL {

//! Renders particles in different colors, depending of their age.
/*!
 *  \ingroup VectoidOpenGL
 */
class AgeColoredParticles : public Vectoid::AgeColoredParticles {
 public:
    AgeColoredParticles(std::shared_ptr<Vectoid::Particles> particles);
    AgeColoredParticles(const AgeColoredParticles &other) = delete;
    AgeColoredParticles &operator=(const AgeColoredParticles &other) = delete;
    void Render(Vectoid::RenderContext *context);
    
  private:
    std::vector<GLfloat> vertexBuffer_,
                         colorBuffer_;
};

}    // Namespace OpenGL.
}    // Namespace Vectoid.
}    // Namespace kxm.

#endif    // KXM_VECTOID_OPENGL_AGECOLOREDPARTICLES_H_
