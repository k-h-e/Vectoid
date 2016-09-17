#ifndef KXM_VECTOID_COORDSYS_H_
#define KXM_VECTOID_COORDSYS_H_

#include <kxm/Vectoid/CoordSysCore.h>

namespace kxm {
namespace Vectoid {

class RenderContext;

//! This scene graph node sets up a local coordinate system for its children.
/*! 
 *  \ingroup Vectoid
 */ 
class CoordSys : public CoordSysCore {
  public:
    CoordSys();
    void Render(RenderContext *context);
    
  private:
    CoordSys(const CoordSys &other);
    CoordSys &operator=(const CoordSys &other);
};

}    // Namespace Vectoid.
}    // Namespace kxm.

#endif    // KXM_VECTOID_COORDSYS_H_
