//
//  CameraProcess.cpp
//  kxm
//
//  Created by Kai Hergenroether on 4/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#include <kxm/Zarch/Video/CameraProcess.h>

#include <kxm/Vectoid/Transform.h>
#include <kxm/Vectoid/CoordSysInterface.h>
#include <kxm/Zarch/MapParameters.h>

using namespace boost;
using namespace kxm::Vectoid;


namespace kxm {
namespace Zarch {

CameraProcess::CameraProcess(shared_ptr<CoordSysInterface> cameraCoordSys,
                             shared_ptr<const LanderProcess::LanderStateInfo> landerState,
                             shared_ptr<const MapParameters> mapParameters)
    : cameraCoordSys_(cameraCoordSys),
      landerState_(landerState),
      mapParameters_(mapParameters),
      cameraState_(new CameraStateInfo()) {
}

shared_ptr<const CameraProcess::CameraStateInfo> CameraProcess::CameraState() {
    return cameraState_;
}

bool CameraProcess::Execute(const Process::Context &context) {
    Vector position = landerState_->transform.TranslationPart();
    if (position.y < mapParameters_->cameraMinHeight)
        position.y = mapParameters_->cameraMinHeight;
    cameraState_->position = Vector(position.x, position.y, position.z + 5.0f);
    cameraCoordSys_->SetPosition(cameraState_->position);
    return true;
}

}    // Namespace Zarch.
}    // Namespace kxm.
