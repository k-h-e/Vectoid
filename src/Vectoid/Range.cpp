#include <kxm/Vectoid/Range.h>

namespace kxm {
namespace Vectoid {

Range::Range()
        : min_(0.0f),
          max_(0.0f),
          undefined_(true) {
    // Nop.
}

Range::Range(float first)
        : min_(first),
          max_(first),
          undefined_(false) {
    // Nop.
}

Range::Range(float number, float anotherNumber)
        : undefined_(false) {
    if (number < anotherNumber) {
        min_ = number;
        max_ = anotherNumber;
    }
    else {
        min_ = anotherNumber;
        max_ = number;
    }
}    

Range::Range(const Range &other, float offset)
        : undefined_(false) {
    min_ = other.min_ + offset;
    max_ = other.max_ + offset;
}

void Range::Grow(float number) {
    if (undefined_) {
        min_       = number;
        max_       = number;
        undefined_ = false;
    }
    else {
        if (number < min_) {
            min_ = number;
        }
        else if (number > max_) {
            max_ = number;
        }
    }
}

}    // Namespace Vectoid.
}    // Namespace kxm.
