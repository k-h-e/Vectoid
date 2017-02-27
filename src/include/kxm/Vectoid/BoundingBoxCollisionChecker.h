#ifndef KXM_VECTOID_BOUNDINGBOXCOLLISIONCHECKER_H_
#define KXM_VECTOID_BOUNDINGBOXCOLLISIONCHECKER_H_

#include <kxm/Vectoid/CollisionCheckerInterface.h>

namespace kxm {
namespace Vectoid {

class BoundingBox;
class Transform;

//! Adapts a bounding box for taking part in collision checking.
/*! 
 *  \ingroup Vectoid
 */ 
class BoundingBoxCollisionChecker : public virtual CollisionCheckerInterface {
  public:
    //! The specified bounding box object is expected to outlive the constructed checker instance.
    BoundingBoxCollisionChecker(const BoundingBox &boundingBox);
    bool CheckCollision(CollisionCheckerInterface *other, const Transform &otherTransform,
                        const Transform &ourTransform);
    bool CheckCollision(BoundingBoxCollisionChecker *other, const Transform &otherTransform,
                        const Transform &ourTransform);
    bool CheckCollision(PointCollisionChecker *other, const Transform &otherTransform,
                        const Transform &ourTransform);
    
  private:
    const BoundingBox &boundingBox_;
};

}    // Namespace Vectoid.
}    // Namespace kxm.

#endif    // KXM_VECTOID_BOUNDINGBOXCOLLISIONCHECKER_H_
