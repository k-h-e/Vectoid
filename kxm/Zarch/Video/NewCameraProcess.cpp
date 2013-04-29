//
//  NewCameraProcess.cpp
//  kxm
//
//  Created by Kai Hergenröther on 4/29/13.
//
//


#include <kxm/Zarch/Video/NewCameraProcess.h>

#include <kxm/Vectoid/CoordSys.h>
#include <kxm/Vectoid/Camera.h>
#include <kxm/Zarch/MapParameters.h>


using namespace boost;
using namespace kxm::Vectoid;


namespace kxm {
namespace Zarch {

NewCameraProcess::NewCameraProcess(const shared_ptr<NewVideo::Data> data)
        : data_(data) {
}

bool NewCameraProcess::Execute(const Process::Context &context) {
    Vector position = data_->landerCoordSys->Position();
    if (position.y < data_->mapParameters->cameraMinHeight)
        position.y = data_->mapParameters->cameraMinHeight;
    data_->camera->SetPosition(Vector(position.x, position.y, position.z + 5.0f));
    return true;
}

}    // Namespace Zarch.
}    // Namespace kxm.
