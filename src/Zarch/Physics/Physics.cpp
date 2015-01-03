//
//  NewPhysics.cpp
//  kxm
//
//  Created by Kai Hergenröther on 4/28/13.
//
//


#include <Zarch/Physics/Physics.h>

#include <kxm/Core/logging.h>
#include <Game/Processes.h>
#include <Zarch/Physics/LanderProcess.h>
#include <Zarch/MapParameters.h>
#include <Zarch/Terrain.h>
#include <Zarch/ControlsState.h>
#include <Zarch/Events/ZarchEvent.h>
#include <Zarch/Events/FrameTimeEvent.h>
#include <Zarch/Events/ControlsStateEvent.h>


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