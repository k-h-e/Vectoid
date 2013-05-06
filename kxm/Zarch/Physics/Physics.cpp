//
//  NewPhysics.cpp
//  kxm
//
//  Created by Kai Hergenröther on 4/28/13.
//
//


#include <kxm/Zarch/Physics/Physics.h>

#include <kxm/Game/Processes.h>
#include <kxm/Zarch/Physics/LanderProcess.h>
#include <kxm/Zarch/MapParameters.h>
#include <kxm/Zarch/Terrain.h>
#include <kxm/Zarch/ControlsState.h>
#include <kxm/Zarch/events.h>


using namespace boost;
using namespace kxm::Game;


namespace kxm {
namespace Zarch {

Physics::Physics(shared_ptr<Processes<ZarchProcess::ProcessType> > processes)
        : processes_(processes) {
    data_ = shared_ptr<Data>(new Data());
    data_->mapParameters = shared_ptr<MapParameters>(new MapParameters());
    data_->terrain       = shared_ptr<Terrain>(new Terrain(data_->mapParameters));
    
    processes_->AddProcess(shared_ptr<Process>(new LanderProcess(data_)));
}

void Physics::HandleEvent(const Event &event) {
    switch (static_cast<const ZarchEvent &>(event).Type()) {
        case ZarchEvent::FrameTimeEvent:
            HandleTimeEvent(static_cast<const PayloadEvent<Variant> &>(event));
            break;
        case ZarchEvent::ControlsStateEvent:
            HandleControlsStateEvent(static_cast<const PayloadEvent<ControlsState> &>(event));
            break;
        default:
            break;
    }
}

void Physics::HandleTimeEvent(const PayloadEvent<Variant> &event) {
    data_->frameDeltaTimeS = event.Data().AsFloat();
}

void Physics::HandleControlsStateEvent(const PayloadEvent<ControlsState> &event) {
    data_->controlsState = event.Data();
}

}    // Namespace Zarch.
}    // Namespace kxm.
