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


using namespace boost;
using namespace kxm::Core;
using namespace kxm::Game;


namespace kxm {
namespace Zarch {

Presentation::Presentation(shared_ptr<ThreadCouplingBuffer> simulationCouplingBuffer,
                           int sendToSimulationDirection)
        : processes_(new Processes<ZarchProcess::ProcessType>()),
          processContext_(*processes_, eventQueue_),
          simulationCouplingBuffer_(simulationCouplingBuffer),
          sendToSimulationDirection_(sendToSimulationDirection) {
    Zarch::RegisterEvents(&eventQueue_);
    
    video_ = shared_ptr<NewVideo>(new NewVideo(processes_));
    eventQueue_.RegisterEventHandler(ZarchEvent::FrameTimeEvent,      video_);
    eventQueue_.RegisterEventHandler(ZarchEvent::LanderMoveEvent,     video_);
    eventQueue_.RegisterEventHandler(ZarchEvent::LanderVelocityEvent, video_);
    eventQueue_.RegisterEventHandler(ZarchEvent::LanderThrusterEvent, video_);
}

void Presentation::PrepareFrame(const ControlsState &controlsState) {
    // We want the next simulation iteration to use the most current controls data, so we schedule
    // the respective event here...
    Event &event = eventQueue_.ScheduleEvent(ZarchEvent::ControlsStateEvent);
    static_cast<PayloadEvent<ControlsState> &>(event).Reset(controlsState);
    
    {
        ThreadCouplingBuffer::Accessor accessor = simulationCouplingBuffer_->Access(
                                                      sendToSimulationDirection_);
        
        eventQueue_.SerializeScheduledEvents(&accessor.SendBuffer());
        Buffer &receiveBuffer = accessor.ReceiveBuffer();
        eventQueue_.DeserializeAndScheduleEvents(receiveBuffer);
        receiveBuffer.Clear();
        
        accessor.SignalUpdateForSendDirection();
            // If necessary, wake the simulation thread for a new iteration.
    }
    eventQueue_.ProcessEvents();
    processes_->ExecuteProcesses(processContext_);
}

}
}

