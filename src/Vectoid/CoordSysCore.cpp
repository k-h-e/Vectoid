//
//  CoordSysCore.cpp
//  kxm
//
//  Created by Kai Hergenroether on 4/6/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#include <Vectoid/CoordSysCore.h>


namespace kxm {
namespace Vectoid {

CoordSysCore::CoordSysCore()
        : transformChanged_(true) {
}

void CoordSysCore::PrependTransform(const Transform &other) {
    transform_.Prepend(other);
    transformChanged_ = true;
}

void CoordSysCore::AppendTransform(const Transform &other) {
    transform_.Append(other);
    transformChanged_ = true;
}

void CoordSysCore::SetTransform(const Transform &other) {
    transform_ = other;
    transformChanged_ = true;
}

void CoordSysCore::GetTransform(Transform *outTransform) const {
    *outTransform = transform_;
}

void CoordSysCore::SetPosition(const Vector &pos) {
    transform_.SetTranslationPart(pos);
    transformChanged_ = true;
}

void CoordSysCore::GetPosition(Vector *outPos) {
    transform_.GetTranslationPart(outPos);
}

Vector CoordSysCore::Position() {
    return transform_.TranslationPart();
}

}    // Namespace Vectoid.
}    // Namespace kxm.