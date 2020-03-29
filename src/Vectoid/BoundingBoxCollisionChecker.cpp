#include <kxm/Vectoid/BoundingBoxCollisionChecker.h>

#include <cstdio>
#include <kxm/Vectoid/Transform.h>
#include <kxm/Vectoid/BoundingBox.h>

namespace kxm {
namespace Vectoid {

BoundingBoxCollisionChecker::BoundingBoxCollisionChecker(const BoundingBox<float> &boundingBox)
        : boundingBox_(boundingBox) {
}

bool BoundingBoxCollisionChecker::CheckCollision(
        CollisionCheckerInterface *other, const Transform<float> &otherTransform,
        const Transform<float> &ourTransform) {
    return other->CheckCollision(this, ourTransform, otherTransform);
}

bool BoundingBoxCollisionChecker::CheckCollision(
        BoundingBoxCollisionChecker *other, const Transform<float> &otherTransform,
        const Transform<float> &ourTransform) {
    return false;    // TODO: Implement check!
}

bool BoundingBoxCollisionChecker::CheckCollision(
        PointCollisionChecker *other, const Transform<float> &otherTransform, const Transform<float> &ourTransform) {
    Vector<float> point;
    otherTransform.GetTranslationPart(&point);
    Transform<float> inverseOurTransform(Transform<float>::InitAsInverse, ourTransform);
    inverseOurTransform.ApplyTo(&point);
    return boundingBox_.Contains(point);
}

}    // Namespace Vectoid.
}    // Namespace kxm.
