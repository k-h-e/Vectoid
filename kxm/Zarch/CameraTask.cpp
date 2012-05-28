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
#include <kxm/Zarch/MapParameters.h>

using boost::shared_ptr;
using namespace kxm::Vectoid;


namespace kxm {
namespace Zarch {

CameraTask::CameraTask(shared_ptr<CoordSysInterface> cameraCoordSys,
                       shared_ptr<const LanderTask::LanderStateInfo> landerState,
                       shared_ptr<const MapParameters> mapParameters)
    : cameraCoordSys_(cameraCoordSys),
      landerState_(landerState),
      mapParameters_(mapParameters) {
}
    
void CameraTask::Execute() {
    Vector position = landerState_->transform.TranslationPart();
    if (position.y < mapParameters_->cameraMinHeight)
        position.y = mapParameters_->cameraMinHeight;
    cameraCoordSys_->SetPosition(Vector(position.x, position.y, position.z + 5.0f));
}


}    // Namespace Zarch.
}    // Namespace kxm.
