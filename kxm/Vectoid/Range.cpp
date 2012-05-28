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
    

}    // Namespace Vectoid.
}    // Namespace kxm.
