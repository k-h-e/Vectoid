#ifndef VECTOID_SCENEGRAPH_PARTICLESRENDERER_H_
#define VECTOID_SCENEGRAPH_PARTICLESRENDERER_H_

#include <vector>
#include <memory>
#include <Vectoid/SceneGraph/GeometryInterface.h>

namespace Vectoid {
namespace Core {
    class Particles;
}
}

namespace Vectoid {
namespace SceneGraph {

//! Renders particles.
class ParticlesRenderer : public virtual GeometryInterface {
  public:
    ParticlesRenderer(const ParticlesRenderer &other) = delete;
    ParticlesRenderer &operator=(const ParticlesRenderer &other) = delete;
    
  protected:
    ParticlesRenderer(const std::shared_ptr<Core::Particles> &particles);
  
    std::shared_ptr<Core::Particles> particles_;
};

}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_PARTICLESRENDERER_H_
