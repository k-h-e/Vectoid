#ifndef KXM_VECTOID_METAL_PERSPECTIVEPROJECTION_H_
#define KXM_VECTOID_METAL_PERSPECTIVEPROJECTION_H_

#include <kxm/Vectoid/PerspectiveProjection.h>

namespace kxm {
namespace Vectoid {
namespace Metal {

class Context;

//! Perspective screen projection, defining a frustum-shaped viewing volume.
/*! 
 *  \ingroup VectoidMetal
 */ 
class PerspectiveProjection : public Vectoid::PerspectiveProjection {
  public:
    PerspectiveProjection(const std::shared_ptr<Context> &context);
    PerspectiveProjection(const PerspectiveProjection &other) = delete;
    PerspectiveProjection &operator=(const PerspectiveProjection &other) = delete;
    void Render();
    
  private:
    std::shared_ptr<Context> context_;
};

}    // Namespace Metal.
}    // Namespace Vectoid.
}    // Namespace kxm.

#endif    // KXM_VECTOID_METAL_PERSPECTIVEPROJECTION_H_
