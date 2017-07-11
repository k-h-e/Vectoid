#include <kxm/Vectoid/PointCollisionChecker.h>

#include <cstdio>
#include <kxm/Vectoid/BoundingBoxCollisionChecker.h>

namespace kxm {
namespace Vectoid {

bool PointCollisionChecker::CheckCollision(CollisionCheckerInterface *other, const Transform &otherTransform,
                                           const Transform &ourTransform) {
    return other->CheckCollision(this, ourTransform, otherTransform);
}

bool PointCollisionChecker::CheckCollision(BoundingBoxCollisionChecker *other, const Transform &otherTransform,
                                           const Transform &ourTransform) {
    return other->CheckCollision(this, ourTransform, otherTransform);
}

bool PointCollisionChecker::CheckCollision(PointCollisionChecker *other, const Transform &otherTransform,
                                           const Transform &ourTransform) {
    return false;    // TODO: Implement check!
}

}    // Namespace Vectoid.
}    // Namespace kxm.
