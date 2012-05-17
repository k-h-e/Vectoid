//
//  Range.cpp
//  kxm
//
//  Created by Kai Hergenroether on 5/6/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


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

void Range::Grow(float number) {
    if (number < min_)
        min_ = number;
    else if (number > max_)
        max_ = number;
}
    
void Range::Clamp(float *number) {
    if (*number < min_)
        *number = min_;
    else if (*number > max_)
        *number = max_;
}

void Range::SetToModuloEquivalent(float *number) {
    float delta = max_ - min_;
    if (delta == 0.0f) {
        *number = min_;
        return;
    }
    if (*number < min_) {
        float distance  = min_ - *number,
              remainder = distance - (float)((int)(distance / delta)) * delta;
        *number = max_ - remainder;
    }
    else if (*number > max_) {
        float distance  = *number - max_,
              remainder = distance - (float)((int)(distance / delta)) * delta;
        *number = min_ + remainder;
    }
    Clamp(number);
    if (*number == max_)
        *number = min_;
}


}    // Namespace Vectoid.
}    // Namespace kxm.
