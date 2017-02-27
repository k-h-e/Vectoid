#ifndef KXM_VECTOID_COLLIDABLEINTERFACE_H_
#define KXM_VECTOID_COLLIDABLEINTERFACE_H_

#include <kxm/Vectoid/HasTransformInterface.h>

namespace kxm {
namespace Vectoid {

class CollisionCheckerInterface;

//! Interface to objects taking part in collision checking.
/*!
 *  \ingroup Vectoid
 */ 
class CollidableInterface : public virtual HasTransformInterface {
  public:
    //! Returns the collidable's collision checker which is guaranteed to live at least as long as the collidable
    //! itself.
    virtual CollisionCheckerInterface *CollisionChecker() = 0;
};

}    // Namespace Vectoid.
}    // Namespace kxm.

#endif    // KXM_VECTOID_COLLIDABLEINTERFACE_H_
