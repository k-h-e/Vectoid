//
//  NewPhysics.cpp
//  kxm
//
//  Created by Kai Hergenröther on 4/28/13.
//
//


#include <kxm/Zarch/Physics/NewPhysics.h>

#include <kxm/Game/Processes.h>
#include <kxm/Zarch/Physics/NewLanderProcess.h>
#include <kxm/Zarch/MapParameters.h>
#include <kxm/Zarch/Terrain.h>
#include <kxm/Zarch/ControlsState.h>
#include <kxm/Zarch/events.h>


using namespace boost;
using namespace kxm::Game;


namespace kxm {
namespace Zarch {

NewPhysics::NewPhysics(shared_ptr<Processes<ZarchProcess::ProcessType> > processes)
        : processes_(processes) {
    data_ = shared_ptr<Data>(new Data());
    data_->mapParameters = shared_ptr<MapParameters>(new MapParameters());
    data_->terrain       = shared_ptr<Terrain>(new Terrain(data_->mapParameters));
    
    processes_->AddProcess(shared_ptr<Process>(new NewLanderProcess(data_)));
}

void NewPhysics::HandleEvent(const Event &event) {
    switch (static_cast<const ZarchEvent &>(event).Type()) {
        case ZarchEvent::FrameTimeEvent:
            HandleTimeEvent(static_cast<const VariantEvent &>(event));
            break;
        case ZarchEvent::ControlsStateEvent:
            HandleControlsStateEvent(static_cast<const ControlsStateEvent &>(event));
            break;
        default:
            break;
    }
}

void NewPhysics::HandleTimeEvent(const VariantEvent &event) {
    data_->frameDeltaTimeS = event.AsFloat();
}

void NewPhysics::HandleControlsStateEvent(const ControlsStateEvent &event) {
    data_->controlsState = event.ControlsState();
}

}    // Namespace Zarch.
}    // Namespace kxm.
