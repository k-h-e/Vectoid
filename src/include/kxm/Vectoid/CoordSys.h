#ifndef KXM_VECTOID_COORDSYS_H_
#define KXM_VECTOID_COORDSYS_H_

#include <kxm/Vectoid/CoordSysCore.h>

namespace kxm {
namespace Vectoid {

//! This scene graph node sets up a local coordinate system for its children.
/*! 
 *  \ingroup Vectoid
 */ 
class CoordSys : public CoordSysCore {
  public:
    CoordSys() {}
    CoordSys(const CoordSys &other) = delete;
    CoordSys &operator=(const CoordSys &other) = delete;
};

}    // Namespace Vectoid.
}    // Namespace kxm.

#endif    // KXM_VECTOID_COORDSYS_H_
