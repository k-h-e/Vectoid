//
//  Simulation.cpp
//  kxm
//
//  Created by Kai Hergenröther on 4/7/13.
//
//


#include <kxm/Zarch/Simulation.h>

#include <kxm/Game/ThreadCouplingBuffer.h>
#include <kxm/Zarch/Zarch.h>
#include <kxm/Zarch/Physics/Physics.h>


using namespace boost;
using namespace kxm::Core;
using namespace kxm::Game;


namespace kxm {
namespace Zarch {

Simulation::Simulation(shared_ptr<ThreadCouplingBuffer> presentationCouplingBuffer,
                       int sendToPresentationDirection)
        : processes_(new Processes<ZarchProcess::ProcessType>()),
          processContext_(*processes_, eventQueue_),
          presentationCouplingBuffer_(presentationCouplingBuffer),
          sendToPresentationDirection_(sendToPresentationDirection),
          lastFrameTime_(posix_time::microsec_clock::local_time()) {
    Zarch::RegisterEvents(&eventQueue_);
    
    physics_ = shared_ptr<Physics>(new Physics(processes_));
    eventQueue_.RegisterEventHandler(ZarchEvent::FrameTimeEvent, physics_);
    eventQueue_.RegisterEventHandler(ZarchEvent::ControlsStateEvent, physics_);
}

void Simulation::ExecuteAction() {
    puts("simulation thread spawned");
    
    uint32_t seqNo, lastSeqNo;
    {
        ThreadCouplingBuffer::Accessor accessor = presentationCouplingBuffer_->Access(
                                                      sendToPresentationDirection_);
        lastSeqNo = accessor.SeqNoForReceiveDirection();
    }
    
    bool shutdownRequested = false;
    while (!shutdownRequested) {
        {
            ThreadCouplingBuffer::Accessor accessor = presentationCouplingBuffer_->Access(
                                                          sendToPresentationDirection_);
            for (;;) {
                seqNo = accessor.SeqNoForReceiveDirection();
                if (seqNo != lastSeqNo) {
                    lastSeqNo = seqNo;
                    break;
                }
                if ((shutdownRequested = accessor.ShutdownRequested()))
                    break;
                accessor.Wait();
            }
            
            GenerateTimeEvent();
            
            eventQueue_.SerializeScheduledEvents(&accessor.SendBuffer());
            Buffer &receiveBuffer = accessor.ReceiveBuffer();
            eventQueue_.DeserializeAndScheduleEvents(receiveBuffer);
            receiveBuffer.Clear();
        }
        eventQueue_.ProcessEvents();
        processes_->ExecuteProcesses(processContext_);
    }
    
    puts("simulation thread terminating");
}

void Simulation::GenerateTimeEvent() {
    posix_time::ptime now = posix_time::microsec_clock::local_time();
    int milliSeconds = (int)((now - lastFrameTime_).total_milliseconds());
    lastFrameTime_ = now;
    float frameDeltaTimeS = (float)milliSeconds / 1000.0f;
    Event &event = processContext_.eventQueue.ScheduleEvent(ZarchEvent::FrameTimeEvent);
    static_cast<PayloadEvent<Variant> &>(event).Data().Reset(frameDeltaTimeS);
}

}
}

