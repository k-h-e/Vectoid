#ifndef VECTOID_CORE_COLLIDABLEINTERFACE_H_
#define VECTOID_CORE_COLLIDABLEINTERFACE_H_

#include <Vectoid/Core/HasTransformInterface.h>

namespace Vectoid {
namespace Core {

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

}    // Namespace Core.
}    // Namespace Vectoid.

#endif    // VECTOID_CORE_COLLIDABLEINTERFACE_H_
