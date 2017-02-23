#include <kxm/Vectoid/CollidableBoundingBox.h>

#include <cstdio>

namespace kxm {
namespace Vectoid {

CollidableBoundingBox::CollidableBoundingBox(const BoundingBox &boundingBox)
        : boundingBox_(boundingBox) {
}

bool CollidableBoundingBox::CheckCollision(const CollidableInterface &other, const Transform &otherTransform,
                                           const Transform &ourTransform) const {
    return other.CheckCollision(*this, ourTransform, otherTransform);
}

bool CollidableBoundingBox::CheckCollision(const CollidableBoundingBox &other, const Transform &otherTransform,
                                           const Transform &ourTransform) const {
    std::puts("    box <-> box");
    return false;    // TODO: Implement check!
}

bool CollidableBoundingBox::CheckCollision(const CollidablePoint &other, const Transform &otherTransform,
                                           const Transform &ourTransform) const {
    std::puts("    box <-> point");
    return false;    // TODO: Implement check!
}

}    // Namespace Vectoid.
}    // Namespace kxm.
