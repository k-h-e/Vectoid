#ifndef VECTOID_SCENEGRAPH_COORDSYS_H_
#define VECTOID_SCENEGRAPH_COORDSYS_H_

#include <Vectoid/SceneGraph/CoordSysCore.h>

namespace Vectoid {
namespace SceneGraph {

//! This scene graph node sets up a local coordinate system for its children.
/*! 
 *  \ingroup Vectoid
 */ 
class CoordSys : public CoordSysCore {
  public:
    CoordSys(const CoordSys &other) = delete;
    CoordSys &operator=(const CoordSys &other) = delete;
    
  protected:
    CoordSys() {}
};

}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_COORDSYS_H_
