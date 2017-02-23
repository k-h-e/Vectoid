#ifndef KXM_VECTOID_COLLIDABLEBOUNDINGBOX_H_
#define KXM_VECTOID_COLLIDABLEBOUNDINGBOX_H_

#include <kxm/Vectoid/CollidableInterface.h>

namespace kxm {
namespace Vectoid {

class BoundingBox;
class Transform;

//! Adapts a bounding box for taking part in collision checking.
/*! 
 *  \ingroup Vectoid
 */ 
class CollidableBoundingBox : public virtual CollidableInterface {
  public:
    //! The specified bounding box object is expected to outlive the constructed collidable instance.
    CollidableBoundingBox(const BoundingBox &boundingBox);
    bool CheckCollision(const CollidableInterface &other, const Transform &otherTransform,
                        const Transform &ourTransform) const;
    bool CheckCollision(const CollidableBoundingBox &other, const Transform &otherTransform,
                        const Transform &ourTransform) const;
    bool CheckCollision(const CollidablePoint &other, const Transform &otherTransform,
                        const Transform &ourTransform) const;
    
  private:
    const BoundingBox &boundingBox_;
};

}    // Namespace Vectoid.
}    // Namespace kxm.

#endif    // KXM_VECTOID_COLLIDABLEBOUNDINGBOX_H_
