//
//  NewPhysics.cpp
//  kxm
//
//  Created by Kai Hergenröther on 4/28/13.
//
//


#include <kxm/Zarch/Physics/Physics.h>

#include <kxm/Core/logging.h>
#include <kxm/Game/Processes.h>
#include <kxm/Zarch/Physics/LanderProcess.h>
#include <kxm/Zarch/MapParameters.h>
#include <kxm/Zarch/Terrain.h>
#include <kxm/Zarch/ControlsState.h>
#include <kxm/Zarch/Events/ZarchEvent.h>
#include <kxm/Zarch/Events/FrameTimeEvent.h>
#include <kxm/Zarch/Events/ControlsStateEvent.h>


using namespace std;
using namespace kxm::Core;
using namespace kxm::Game;


namespace kxm {
namespace Zarch {

Physics::Physics(shared_ptr<Processes<ZarchProcess::ProcessType>> processes)
        : processes_(processes) {
    data_ = shared_ptr<Data>(new Data());
    data_->mapParameters = shared_ptr<MapParameters>(new MapParameters());
    data_->terrain       = shared_ptr<Terrain>(new Terrain(data_->mapParameters));
    
    processes_->AddProcess(shared_ptr<Process>(new LanderProcess(data_)));
}

void Physics::HandleEvent(const Game::Event &event) {
    static_cast<const ZarchEvent &>(event).DispatchToPhysics(this);
}

void Physics::HandleFrameTimeEvent(const FrameTimeEvent &event) {
    data_->frameDeltaTimeS = event.timeS;
}

void Physics::HandleControlsStateEvent(const ControlsStateEvent &event) {
    data_->controlsState = event.controlsState;
}

}    // Namespace Zarch.
}    // Namespace kxm.
