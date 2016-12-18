#ifndef KXM_VECTOID_COLLIDABLEINTERFACE_H_
#define KXM_VECTOID_COLLIDABLEINTERFACE_H_

#include <kxm/Core/Interface.h>

namespace kxm {
namespace Vectoid {

//! Interface to objects taking part in collision checking.
/*! 
 *  \ingroup Vectoid
 */ 
class CollidableInterface : public virtual Core::Interface {
  public:
};

}    // Namespace Vectoid.
}    // Namespace kxm.

#endif    // KXM_VECTOID_COLLIDABLEINTERFACE_H_
