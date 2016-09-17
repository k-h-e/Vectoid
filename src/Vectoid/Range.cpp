#include <kxm/Vectoid/Range.h>

namespace kxm {
namespace Vectoid {

Range::Range(float first) {
    min_ = first;
    max_ = first;
}

Range::Range(float number, float anotherNumber) {
    if (number < anotherNumber) {
        min_ = number;
        max_ = anotherNumber;
    }
    else {
        min_ = anotherNumber;
        max_ = number;
    }
}    

Range::Range(const Range &other, float offset) {
    min_ = other.min_ + offset;
    max_ = other.max_ + offset;
}

void Range::Grow(float number) {
    if (number < min_)
        min_ = number;
    else if (number > max_)
        max_ = number;
}

}    // Namespace Vectoid.
}    // Namespace kxm.
