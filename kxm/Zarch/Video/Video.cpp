//
//  Video.cpp
//  kxm
//
//  Created by Kai Hergenröther on 12/3/12.
//
//


#include <kxm/Zarch/Video/Video.h>

#include <kxm/Core/logging.h>
#include <kxm/Zarch/Video/CameraProcess.h>
#include <kxm/Zarch/Video/TerrainProcess.h>
#include <kxm/Zarch/Video/StarFieldProcess.h>
#include <kxm/Zarch/events.h>

using namespace std;
using namespace boost;
using namespace kxm::Vectoid;
using namespace kxm::Game;


namespace kxm {
namespace Zarch {

Video::Video(EventQueue<ZarchEvent::EventType> *eventQueue,
             shared_ptr<MapParameters> mapParameters, shared_ptr<CoordSysInterface> camera,
             shared_ptr<TerrainRenderer> terrainRenderer, shared_ptr<Particles> starFieldParticles)
        : processContext_(processes_, *eventQueue),
          landerStateInfo_(new LanderProcess::LanderStateInfo()) {
    shared_ptr<CameraProcess> cameraProcess(
        new CameraProcess(camera, landerStateInfo_, mapParameters));
    processes_.AddProcess(cameraProcess);
    processes_.AddProcess(shared_ptr<Process>(
        new TerrainProcess(terrainRenderer, landerStateInfo_)));
    processes_.AddProcess(shared_ptr<Process>(
        new StarFieldProcess(starFieldParticles, cameraProcess->CameraState(), mapParameters)));
}

void Video::HandleEvent(const Event &event) {
    switch (static_cast<const ZarchEvent &>(event).Type()) {
        case ZarchEvent::LanderMoveEvent:
            landerStateInfo_->transform
                = static_cast<const PayloadEvent<Transform> &>(event).Data();
            break;
        default:
            break;
    }
}

void Video::ExecuteProcesses() {
    processes_.ExecuteProcesses(processContext_);
}

}    // Namespace Zarch.
}    // Namespace kxm.
