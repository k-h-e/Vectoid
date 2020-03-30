#ifndef VECTOID_SCENEGRAPH_AGECOLOREDPARTICLES_H_
#define VECTOID_SCENEGRAPH_AGECOLOREDPARTICLES_H_

#include <vector>
#include <memory>
#include <Vectoid/Core/Vector.h>
#include <Vectoid/SceneGraph/GeometryInterface.h>

namespace Vectoid {
namespace Core {
    class Particles;
}
}

namespace Vectoid {
namespace SceneGraph {

//! Renders particles in different colors, depending of their age.
/*!
 *  \ingroup Vectoid
 */
class AgeColoredParticles : public virtual GeometryInterface {
 public:
    AgeColoredParticles(const AgeColoredParticles &other) = delete;
    AgeColoredParticles &operator=(const AgeColoredParticles &other) = delete;
    
  protected:
    AgeColoredParticles(const std::shared_ptr<Core::Particles> &particles);
  
    std::shared_ptr<Core::Particles> particles_;
    float                            highAge_;
    std::vector<Core::Vector<float>> colors_;
};

}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_AGECOLOREDPARTICLES_H_
