#ifndef KXM_VECTOID_METAL_COORDSYS_H_
#define KXM_VECTOID_METAL_COORDSYS_H_

#include <kxm/Vectoid/CoordSys.h>

namespace kxm {
namespace Vectoid {
namespace Metal {

//! This scene graph node sets up a local coordinate system for its children.
/*! 
 *  \ingroup VectoidMetal
 */ 
class CoordSys : public Vectoid::CoordSys {
  public:
    CoordSys();
    CoordSys(const CoordSys &other) = delete;
    CoordSys &operator=(const CoordSys &other) = delete;
    void Render();
};

}    // Namespace Metal.
}    // Namespace Vectoid.
}    // Namespace kxm.

#endif    // KXM_VECTOID_METAL_COORDSYS_H_
