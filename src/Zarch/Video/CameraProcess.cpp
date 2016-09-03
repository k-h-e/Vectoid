//
//  NewCameraProcess.cpp
//  kxm
//
//  Created by Kai Hergenröther on 4/29/13.
//
//


#include <Zarch/Video/CameraProcess.h>

#include <Vectoid/CoordSys.h>
#include <Vectoid/Camera.h>
#include <Zarch/MapParameters.h>


using namespace std;
using namespace kxm::Vectoid;


namespace kxm {

namespace Game {
    class ExecutionContext;
}

namespace Zarch {
namespace Video {

CameraProcess::CameraProcess(const shared_ptr<Video::Data> data)
        : data_(data) {
}

void CameraProcess::Execute() {
    Vector position = data_->landerCoordSys->Position();
    if (position.y < data_->mapParameters->cameraMinHeight)
        position.y = data_->mapParameters->cameraMinHeight;
    data_->camera->SetPosition(Vector(position.x, position.y, position.z + 5.0f));
}

bool CameraProcess::Finished() {
    return false;
}

}    // Namespace Video.
}    // Namespace Zarch.
}    // Namespace kxm.
