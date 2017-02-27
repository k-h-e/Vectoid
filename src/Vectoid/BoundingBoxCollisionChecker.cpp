#include <kxm/Vectoid/BoundingBoxCollisionChecker.h>

#include <cstdio>

namespace kxm {
namespace Vectoid {

BoundingBoxCollisionChecker::BoundingBoxCollisionChecker(const BoundingBox &boundingBox)
        : boundingBox_(boundingBox) {
}

bool BoundingBoxCollisionChecker::CheckCollision(CollisionCheckerInterface *other,
                                                 const Transform &otherTransform, const Transform &ourTransform) {
    return other->CheckCollision(this, ourTransform, otherTransform);
}

bool BoundingBoxCollisionChecker::CheckCollision(BoundingBoxCollisionChecker *other,
                                                 const Transform &otherTransform, const Transform &ourTransform) {
    std::puts("    box <-> box");
    return false;    // TODO: Implement check!
}

bool BoundingBoxCollisionChecker::CheckCollision(PointCollisionChecker *other,
                                                 const Transform &otherTransform, const Transform &ourTransform) {
    std::puts("    box <-> point");
    return false;    // TODO: Implement check!
}

}    // Namespace Vectoid.
}    // Namespace kxm.
