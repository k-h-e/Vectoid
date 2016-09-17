#ifndef KXM_VECTOID_AGECOLOREDPARTICLES_H_
#define KXM_VECTOID_AGECOLOREDPARTICLES_H_

#include <vector>
#include <memory>
#include <kxm/Vectoid/OpenGL.h>
#include <kxm/Vectoid/Vector.h>
#include <kxm/Vectoid/GeometryInterface.h>

namespace kxm {
namespace Vectoid {

class Particles;

//! Renders particles in different colors, depending of their age.
/*!
 *  \ingroup Vectoid
 */
class AgeColoredParticles : public virtual GeometryInterface {
 public:
    AgeColoredParticles(std::shared_ptr<Vectoid::Particles> particles);
    
    void Render(Vectoid::RenderContext *context);
    
  private:
    AgeColoredParticles(const AgeColoredParticles &other);
    AgeColoredParticles &operator=(const AgeColoredParticles &other);
    
    std::shared_ptr<Vectoid::Particles> particles_;
    float                               highAge_;
    std::vector<Vectoid::Vector>        colors_;
    std::vector<GLfloat>                vertexBuffer_,
                                        colorBuffer_;
};

}    // Namespace Vectoid.
}    // Namespace kxm.

#endif    // KXM_VECTOID_AGECOLOREDPARTICLES_H_
