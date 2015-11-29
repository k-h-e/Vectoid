//
//  Presentation.cpp
//  kxm
//
//  Created by Kai Hergenröther on 4/7/13.
//
//


#include <Zarch/Presentation.h>

#include <kxm/Core/logging.h>
#include <Zarch/ControlsState.h>
#include <Zarch/Zarch.h>
#include <Zarch/Events/FrameTimeEvent.h>
#include <Zarch/Events/LanderMoveEvent.h>
#include <Zarch/Events/LanderVelocityEvent.h>
#include <Zarch/Events/LanderThrusterEvent.h>
#include <Zarch/Events/ControlsStateEvent.h>


using namespace std;
using namespace kxm::Core;
using namespace kxm::Game;


namespace kxm {
namespace Zarch {

Presentation::Presentation(const shared_ptr<EventQueueHub> &eventQueueHub)
        : eventQueue_(new EventQueue(EventQueueHub::initialBufferSize)),
          processes_(new Processes<ZarchProcess::ProcessType>()),
          eventQueueHub_(eventQueueHub) {
    Zarch::RegisterEvents(eventQueue_.get());
    hubClientId_ = eventQueueHub_->AllocUniqueClientId();
    
    video_ = shared_ptr<Video>(new Video(eventQueue_, processes_));
}

void Presentation::PrepareFrame(const ControlsState &controlsState) {
    // We want the next simulation iteration to use the most current controls data, so we schedule
    // the respective event here...
    eventQueue_->Schedule(ControlsStateEvent(controlsState));
    
    eventQueue_->SyncWithHub(eventQueueHub_.get(), hubClientId_, false);
    eventQueue_->ProcessEvents();
    
    processes_->ExecuteProcesses();
}

}
}

