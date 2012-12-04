//
//  Physics.cpp
//  kxm
//
//  Created by Kai Hergenröther on 12/3/12.
//
//


#include <kxm/Zarch/Physics/Physics.h>

#include <kxm/Core/logging.h>
#include <kxm/Zarch/Physics/LanderProcess.h>
#include <kxm/Zarch/Physics/ThrusterParticlesProcess.h>
#include <kxm/Zarch/Physics/ShotsProcess.h>
#include <kxm/Zarch/ControlsState.h>
#include <kxm/Zarch/events.h>

using namespace std;
using namespace boost;
using namespace kxm::Core;
using namespace kxm::Vectoid;
using namespace kxm::Game;


namespace kxm {
namespace Zarch {

Physics::Physics(
    EventQueue<ZarchEvent::EventType> *eventQueue,
    shared_ptr<MapParameters> mapParameters, shared_ptr<Terrain> terrain,
    shared_ptr<CoordSysInterface> landerCoordSys, shared_ptr<Particles> thrusterParticles,
    shared_ptr<Particles> shotsParticles)
        : frameTimeInfo_(new FrameTimeProcess::FrameTimeInfo()),
          controlsState_(new ControlsState()) {
    LanderProcess *landerProcess = new LanderProcess(
        landerCoordSys, frameTimeInfo_, controlsState_, terrain, mapParameters);
    processes_.AddProcess(landerProcess);
    processes_.AddProcess(
        new ThrusterParticlesProcess(thrusterParticles, landerProcess->LanderState(),
                                     frameTimeInfo_, mapParameters));
    processes_.AddProcess(
        new ShotsProcess(shotsParticles, landerProcess->LanderState(), frameTimeInfo_,
                         mapParameters));
              
    processContext_.eventQueue = eventQueue;
    processContext_.processes  = &processes_;
}

void Physics::HandleEvent(const Event *event) {
    switch (static_cast<const ZarchEvent *>(event)->Type()) {
        case ZarchEvent::FrameTimeEvent:
            frameTimeInfo_->timeSinceLastFrame
                = static_cast<const VariantEvent *>(event)->AsFloat();
            break;
        case ZarchEvent::ControlsStateEvent:
            *controlsState_ = static_cast<const ControlsStateEvent *>(event)->ControlsState();
            break;
        default:
            break;
    }
}

void Physics::ExecuteProcesses() {
    processes_.ExecuteProcesses(processContext_);
}

}    // Namespace Zarch.
}    // Namespace kxm.
