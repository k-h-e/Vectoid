//
//  Simulation.cpp
//  kxm
//
//  Created by Kai Hergenröther on 4/7/13.
//
//


#include <kxm/Zarch/Simulation.h>

#include <kxm/Game/ThreadCouplingBuffer.h>
#include <kxm/Zarch/NewFrameTimeProcess.h>
#include <kxm/Zarch/Zarch.h>


using namespace boost;
using namespace kxm::Core;
using namespace kxm::Game;


namespace kxm {
namespace Zarch {

Simulation::Simulation(shared_ptr<ThreadCouplingBuffer> presentationCouplingBuffer,
                       int sendToPresentationDirection)
        : processContext_(processes_, eventQueue_),
          presentationCouplingBuffer_(presentationCouplingBuffer),
          sendToPresentationDirection_(sendToPresentationDirection) {
    Zarch::RegisterEvents(&eventQueue_);
    processes_.AddProcess(shared_ptr<Process>(new NewFrameTimeProcess()));
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
            
            eventQueue_.SerializeScheduledEvents(&accessor.SendBuffer());
            Buffer &receiveBuffer = accessor.ReceiveBuffer();
            eventQueue_.DeserializeAndScheduleEvents(receiveBuffer);
            receiveBuffer.Clear();
        }
        eventQueue_.ProcessEvents();
        processes_.ExecuteProcesses(processContext_);
    }
    
    puts("simulation thread terminating");
}

}
}

