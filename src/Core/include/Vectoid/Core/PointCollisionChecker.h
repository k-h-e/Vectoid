#ifndef VECTOID_CORE_POINTCOLLISIONCHECKER_H_
#define VECTOID_CORE_POINTCOLLISIONCHECKER_H_

#include <Vectoid/Core/CollisionCheckerInterface.h>

namespace Vectoid {
namespace Core {

//! Point taking part in collision checking.
/*! 
 *  \ingroup Vectoid
 */ 
class PointCollisionChecker : public virtual CollisionCheckerInterface {
  public:
    bool CheckCollision(CollisionCheckerInterface *other, const Transform<float> &otherTransform,
                        const Transform<float> &ourTransform);
    bool CheckCollision(BoundingBoxCollisionChecker *other, const Transform<float> &otherTransform,
                        const Transform<float> &ourTransform);
    bool CheckCollision(PointCollisionChecker *other, const Transform<float> &otherTransform,
                        const Transform<float> &ourTransform);
};

}    // Namespace Core.
}    // Namespace Vectoid.

#endif    // VECTOID_CORE_POINTCOLLISIONCHECKER_H_
