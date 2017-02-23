#ifndef KXM_VECTOID_COLLIDABLEPOINT_H_
#define KXM_VECTOID_COLLIDABLEPOINT_H_

#include <kxm/Vectoid/CollidableInterface.h>

namespace kxm {
namespace Vectoid {

//! Point taking part in collision checking.
/*! 
 *  \ingroup Vectoid
 */ 
class CollidablePoint : public virtual CollidableInterface {
  public:
    bool CheckCollision(const CollidableInterface &other, const Transform &otherTransform,
                        const Transform &ourTransform) const;
    bool CheckCollision(const CollidableBoundingBox &other, const Transform &otherTransform,
                        const Transform &ourTransform) const;
    bool CheckCollision(const CollidablePoint &other, const Transform &otherTransform,
                        const Transform &ourTransform) const;
};

}    // Namespace Vectoid.
}    // Namespace kxm.

#endif    // KXM_VECTOID_COLLIDABLEPOINT_H_
