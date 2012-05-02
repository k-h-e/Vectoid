//
//  CameraTask.cpp
//  kxm
//
//  Created by Kai Hergenroether on 4/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#include <kxm/Zarch/CameraTask.h>

#include <kxm/Vectoid/Transform.h>
#include <kxm/Vectoid/CoordSysInterface.h>

using boost::shared_ptr;
using namespace kxm::Vectoid;


namespace kxm {
namespace Zarch {

CameraTask::CameraTask(shared_ptr<CoordSysInterface> cameraCoordSys,
                       shared_ptr<const Transform> landerTransform)
    : cameraCoordSys_(cameraCoordSys),
      landerTransform_(landerTransform) {
}
    
void CameraTask::Execute() {
    Vector position = landerTransform_->TranslationPart();
    cameraCoordSys_->SetPosition(Vector(position.x, position.y, position.z + 5.0f));
}


}    // Namespace Zarch.
}    // Namespace kxm.
