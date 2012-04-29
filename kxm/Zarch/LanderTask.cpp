//
//  File.cpp
//  kxm
//
//  Created by Kai Hergenroether on 4/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#include <kxm/Zarch/LanderTask.h>

#include <kxm/Vectoid/Transform.h>
#include <kxm/Vectoid/CoordSysInterface.h>

using boost::shared_ptr;
using namespace kxm::Vectoid;


namespace kxm {
namespace Zarch {

LanderTask::LanderTask(shared_ptr<CoordSysInterface> landerCoordSys)
        : landerCoordSys_(landerCoordSys),
          landerTransform_(new Transform()),
          animationAngle_(0.0f) {
}

shared_ptr<const Vectoid::Transform> LanderTask::LanderTransform() {
    return landerTransform_;
}

void LanderTask::Execute() {
    landerTransform_->Prepend(Transform(YAxis, 3.0f));
    animationAngle_ += 1.0f;
    if (animationAngle_ >= 360.0f)
        animationAngle_ = 0.0f;
    float rad = animationAngle_ * 3.141592654f / 180.0f;
    Vector position(cos(rad) * 8.0f, 2.5f, sin(rad) * 8.0f); 
    landerTransform_->SetTranslationPart(position);
    landerCoordSys_->SetTransform(*landerTransform_);
}

}
}

