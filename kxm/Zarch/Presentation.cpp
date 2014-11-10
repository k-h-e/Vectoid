//
//  Presentation.cpp
//  kxm
//
//  Created by Kai Hergenröther on 4/7/13.
//
//


#include <kxm/Zarch/Presentation.h>

#include <kxm/Game/ThreadCouplingBuffer.h>
#include <kxm/Zarch/ControlsState.h>
#include <kxm/Zarch/Zarch.h>
#include <kxm/Zarch/Events/FrameTimeEvent.h>
#include <kxm/Zarch/Events/LanderMoveEvent.h>
#include <kxm/Zarch/Events/LanderVelocityEvent.h>
#include <kxm/Zarch/Events/LanderThrusterEvent.h>


using namespace std;
using namespace kxm::Core;
using namespace kxm::Game;


namespace kxm {
namespace Zarch {

Presentation::Presentation(shared_ptr<ThreadCouplingBuffer> simulationCouplingBuffer,
                           int sendToSimulationDirection)
        : processes_(new Processes<ZarchProcess::ProcessType>()),
          processContext_(*processes_, oldEventQueue_),
          simulationCouplingBuffer_(simulationCouplingBuffer),
          sendToSimulationDirection_(sendToSimulationDirection) {
    Zarch::RegisterEvents(&eventQueue_);
    
    video_ = shared_ptr<Video>(new Video(processes_));
    eventQueue_.AddHandler(FrameTimeEvent::type,      video_);
    eventQueue_.AddHandler(LanderMoveEvent::type,     video_);
    eventQueue_.AddHandler(LanderVelocityEvent::type, video_);
    eventQueue_.AddHandler(LanderThrusterEvent::type, video_);
    
    Zarch::RegisterEvents(&oldEventQueue_);
    oldEventQueue_.RegisterEventHandler(OldZarchEvent::FrameTimeEvent,      video_);
    oldEventQueue_.RegisterEventHandler(OldZarchEvent::LanderMoveEvent,     video_);
    oldEventQueue_.RegisterEventHandler(OldZarchEvent::LanderVelocityEvent, video_);
    oldEventQueue_.RegisterEventHandler(OldZarchEvent::LanderThrusterEvent, video_);
}

void Presentation::PrepareFrame(const ControlsState &controlsState) {
    // We want the next simulation iteration to use the most current controls data, so we schedule
    // the respective event here...
    oldEventQueue_.ScheduleEvent<OldEvent<ControlsState>>(OldZarchEvent::ControlsStateEvent)
                  .Reset(controlsState);
    
    {
        ThreadCouplingBuffer::Accessor accessor = simulationCouplingBuffer_->Access(
                                                      sendToSimulationDirection_);
        
        oldEventQueue_.SerializeScheduledEvents(&accessor.SendBuffer());
        Buffer &receiveBuffer = accessor.ReceiveBuffer();
        oldEventQueue_.DeserializeAndScheduleEvents(receiveBuffer);
        receiveBuffer.Clear();
        
        accessor.SignalUpdateForSendDirection();
            // If necessary, wake the simulation thread for a new iteration.
    }
    oldEventQueue_.ProcessEvents();
    processes_->ExecuteProcesses(processContext_);
}

}
}

