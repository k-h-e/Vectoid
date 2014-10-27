//
//  NewCameraProcess.cpp
//  kxm
//
//  Created by Kai Hergenröther on 4/29/13.
//
//


#include <kxm/Zarch/Video/CameraProcess.h>

#include <kxm/Vectoid/CoordSys.h>
#include <kxm/Vectoid/Camera.h>
#include <kxm/Zarch/MapParameters.h>


using namespace std;
using namespace kxm::Vectoid;


namespace kxm {

namespace Game {
    class ExecutionContext;
}

namespace Zarch {

CameraProcess::CameraProcess(const shared_ptr<Video::Data> data)
        : data_(data) {
}

bool CameraProcess::Execute(const Game::ExecutionContext &context) {
    Vector position = data_->landerCoordSys->Position();
    if (position.y < data_->mapParameters->cameraMinHeight)
        position.y = data_->mapParameters->cameraMinHeight;
    data_->camera->SetPosition(Vector(position.x, position.y, position.z + 5.0f));
    return true;
}

}    // Namespace Zarch.
}    // Namespace kxm.
