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
          direction_(0.0f, 0.0f, -1.0f) {
}

shared_ptr<const Vectoid::Transform> LanderTask::LanderTransform() {
    return landerTransform_;
}

void LanderTask::Execute() {
    Vector position = landerTransform_->TranslationPart();
    
    Transform transform(XAxis, 40.0f);
    Vector gravity = *acceleration_;
    transform.ApplyTo(&gravity);
    float projection = gravity.x;
    Tools::Clamp(&projection, -1.0f, 1.0f);
    float xAngle = (float)asin(projection) * 180.0f / 3.141592654f;
    projection = gravity.y;
    Tools::Clamp(&projection, -1.0f, 1.0f);
    float yAngle = -(float)asin(projection) * 180.0f / 3.141592654f;
    float maxAngle    = 30.0f,
          speedFactor =   .5f;
    Tools::Clamp(&xAngle, -maxAngle, maxAngle);
    Tools::Clamp(&yAngle, -maxAngle, maxAngle);
    Vector speed(xAngle / maxAngle, 0.0f, yAngle / maxAngle),
           speedDirection = speed;
    float  speedLength    = speed.Length();
    Tools::Clamp(&speedLength, 0.0f, 1.0f);
    if (speedLength > 0.0f)
        direction_ = (1.0f/speedLength) * speedDirection;
    
    Vector up(0.0f, 1.0f, 0.0f);
    landerTransform_->SetRotationPart(CrossProduct(up, -direction_), up, -direction_);
    landerTransform_->Prepend(Transform(XAxis, -speedLength * 40.0f));
    landerTransform_->Prepend(Transform(YAxis, 180.0));
    
    position.x += speedFactor * speed.x;
    position.y  = 4.5f;
    position.z += speedFactor * speed.z;
    landerTransform_->SetTranslationPart(position);
    
    landerCoordSys_->SetTransform(*landerTransform_);
}

}
}

