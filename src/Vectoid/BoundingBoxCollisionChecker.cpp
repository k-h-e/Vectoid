#include <kxm/Vectoid/BoundingBoxCollisionChecker.h>

#include <cstdio>
#include <kxm/Vectoid/Transform.h>
#include <kxm/Vectoid/BoundingBox.h>

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
    return false;    // TODO: Implement check!
}

bool BoundingBoxCollisionChecker::CheckCollision(PointCollisionChecker *other,
                                                 const Transform &otherTransform, const Transform &ourTransform) {
    Vector point;
    otherTransform.GetTranslationPart(&point);
    Transform inverseOurTransform(Transform::InitAsInverse, ourTransform);
    inverseOurTransform.ApplyTo(&point);
    return boundingBox_.Contains(point);
}

}    // Namespace Vectoid.
}    // Namespace kxm.
