#ifndef KXM_VECTOID_PARTICLESRENDERER_H_
#define KXM_VECTOID_PARTICLESRENDERER_H_

#include <vector>
#include <memory>

#include <kxm/Vectoid/OpenGL.h>
#include <kxm/Vectoid/GeometryInterface.h>

namespace kxm {
namespace Vectoid {
    
class RenderContext;
class Particles;

//! Renders particles.
/*!
 *  \ingroup Vectoid
 */
class ParticlesRenderer : public virtual Vectoid::GeometryInterface {
  public:
    ParticlesRenderer(std::shared_ptr<Vectoid::Particles> particles);
    
    void Render(Vectoid::RenderContext *context);
    
  private:
    ParticlesRenderer(const ParticlesRenderer &other);
    ParticlesRenderer &operator=(const ParticlesRenderer &other);
    
    std::shared_ptr<Vectoid::Particles> particles_;
    std::vector<GLfloat>                vertexBuffer_;
};


}    // Namespace Vectoid.
}    // Namespace kxm.


#endif    // KXM_VECTOID_PARTICLESRENDERER_H_
