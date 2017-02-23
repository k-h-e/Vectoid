#include <kxm/Vectoid/CollidablePoint.h>

#include <cstdio>
#include <kxm/Vectoid/CollidableBoundingBox.h>

namespace kxm {
namespace Vectoid {

bool CollidablePoint::CheckCollision(const CollidableInterface &other, const Transform &otherTransform,
                                     const Transform &ourTransform) const {
    return other.CheckCollision(*this, ourTransform, otherTransform);
}

bool CollidablePoint::CheckCollision(const CollidableBoundingBox &other, const Transform &otherTransform,
                                     const Transform &ourTransform) const {
    std::puts("    [point <-> box]");
    return other.CheckCollision(*this, ourTransform, otherTransform);
}

bool CollidablePoint::CheckCollision(const CollidablePoint &other, const Transform &otherTransform,
                                     const Transform &ourTransform) const {
    std::puts("    point <-> point");
    return false;    // TODO: Implement check!
}

}    // Namespace Vectoid.
}    // Namespace kxm.
