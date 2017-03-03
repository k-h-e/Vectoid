#include <kxm/Vectoid/BoundingBox.h>

namespace kxm {
namespace Vectoid {

BoundingBox::BoundingBox() {
    // Nop.
}

void BoundingBox::Grow(const Vector &point) {
    xRange_.Grow(point.x);
    yRange_.Grow(point.y);
    zRange_.Grow(point.z);
}

}    // Namespace Vectoid.
}    // Namespace kxm.
