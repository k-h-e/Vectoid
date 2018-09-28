#ifndef KXM_VECTOID_METAL_PERSPECTIVEPROJECTION_H_
#define KXM_VECTOID_METAL_PERSPECTIVEPROJECTION_H_

#include <kxm/Vectoid/PerspectiveProjection.h>

namespace kxm {
namespace Vectoid {
namespace Metal {

class RenderTarget;
class Context;

//! Perspective screen projection, defining a frustum-shaped viewing volume.
/*! 
 *  \ingroup VectoidMetal
 */ 
class PerspectiveProjection : public Vectoid::PerspectiveProjection {
  public:
    friend class RenderTarget;
    
    PerspectiveProjection(const PerspectiveProjection &other) = delete;
    PerspectiveProjection &operator=(const PerspectiveProjection &other) = delete;
    void Render();
    
  private:
    PerspectiveProjection(const std::shared_ptr<Context> &context);
    
    std::shared_ptr<Context> context_;
};

}    // Namespace Metal.
}    // Namespace Vectoid.
}    // Namespace kxm.

#endif    // KXM_VECTOID_METAL_PERSPECTIVEPROJECTION_H_
