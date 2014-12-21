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
        : eventQueue_(EventQueueHub::initialBufferSize),
          eventQueueHub_(eventQueueHub),
          processes_(new Processes<ZarchProcess::ProcessType>()),
          processContext_(*processes_, eventQueue_) {
    Zarch::RegisterEvents(&eventQueue_);
    
    video_ = shared_ptr<Video>(new Video(processes_));
    eventQueue_.AddHandler(FrameTimeEvent::type,      video_);
    eventQueue_.AddHandler(LanderMoveEvent::type,     video_);
    eventQueue_.AddHandler(LanderVelocityEvent::type, video_);
    eventQueue_.AddHandler(LanderThrusterEvent::type, video_);
    
    hubClientId_ = eventQueueHub_->AllocUniqueClientId();
}

void Presentation::PrepareFrame(const ControlsState &controlsState) {
    // We want the next simulation iteration to use the most current controls data, so we schedule
    // the respective event here...
    eventQueue_.Schedule(ControlsStateEvent(controlsState));
    
    eventQueue_.SyncWithHub(eventQueueHub_.get(), hubClientId_, false);
    eventQueue_.ProcessEvents();
    
    processes_->ExecuteProcesses(processContext_);
}

}
}

