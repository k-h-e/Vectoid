//
//  Presentation.cpp
//  kxm
//
//  Created by Kai Hergenröther on 4/7/13.
//
//


#include <kxm/Zarch/Presentation.h>

#include <kxm/Game/ThreadCouplingBuffer.h>
#include <kxm/Zarch/Zarch.h>


using namespace boost;
using namespace kxm::Core;
using namespace kxm::Game;


namespace kxm {
namespace Zarch {

Presentation::Presentation(shared_ptr<ThreadCouplingBuffer> simulationCouplingBuffer,
                           int sendToSimulationDirection)
        : processContext_(processes_, eventQueue_),
          simulationCouplingBuffer_(simulationCouplingBuffer),
          sendToSimulationDirection_(sendToSimulationDirection) {
    Zarch::RegisterEvents(&eventQueue_);
}

void Presentation::PrepareFrame(const ControlsState &controlsState) {
    // We want the next simulation iteration to use the most current controls data, so we schedule
    // the respective event here...
    Event &event = eventQueue_.ScheduleEvent(ZarchEvent::ControlsStateEvent);
    static_cast<ControlsStateEvent &>(event).Reset(controlsState);
    
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
    processes_.ExecuteProcesses(processContext_);
}

void Presentation::SetViewPort(int width, int height) {
}

void Presentation::RenderFrame() {
}

}
}

