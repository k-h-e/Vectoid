#ifndef KXM_VECTOID_POINTCOLLISIONCHECKER_H_
#define KXM_VECTOID_POINTCOLLISIONCHECKER_H_

#include <kxm/Vectoid/CollisionCheckerInterface.h>

namespace kxm {
namespace Vectoid {

//! Point taking part in collision checking.
/*! 
 *  \ingroup Vectoid
 */ 
class PointCollisionChecker : public virtual CollisionCheckerInterface {
  public:
    bool CheckCollision(CollisionCheckerInterface *other, const Transform &otherTransform,
                        const Transform &ourTransform);
    bool CheckCollision(BoundingBoxCollisionChecker *other, const Transform &otherTransform,
                        const Transform &ourTransform);
    bool CheckCollision(PointCollisionChecker *other, const Transform &otherTransform,
                        const Transform &ourTransform);
};

}    // Namespace Vectoid.
}    // Namespace kxm.

#endif    // KXM_VECTOID_POINTCOLLISIONCHECKER_H_
