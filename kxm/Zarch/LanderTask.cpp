//
//  File.cpp
//  kxm
//
//  Created by Kai Hergenroether on 4/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#include <kxm/Zarch/LanderTask.h>

#include <kxm/Core/Tools.h>
#include <kxm/Vectoid/Transform.h>
#include <kxm/Vectoid/CoordSysInterface.h>

using boost::shared_ptr;
using namespace kxm::Core;
using namespace kxm::Vectoid;


namespace kxm {
namespace Zarch {

LanderTask::LanderTask(shared_ptr<CoordSysInterface> landerCoordSys,
                       shared_ptr<const Vector> acceleration)
        : landerCoordSys_(landerCoordSys),
          acceleration_(acceleration),
          landerTransform_(new Transform()),
          animationAngle_(0.0f) {
}

shared_ptr<const Vectoid::Transform> LanderTask::LanderTransform() {
    return landerTransform_;
}

void LanderTask::Execute() {
    landerTransform_->Prepend(Transform(YAxis, 3.0f));
    
    Vector position = landerTransform_->TranslationPart();
    position.y = 3.0f;
    float yAccel = acceleration_->y;
    Tools::Clamp(&yAccel, -1.0f, 1.0f);
    float angle = (float)acos(yAccel) * 180.0f / 3.141592654f;
    position.x += acceleration_->x;
    position.z += (angle - 135.0f) / 30.0f;
    landerTransform_->SetTranslationPart(position);
    landerCoordSys_->SetTransform(*landerTransform_);
}

}
}

