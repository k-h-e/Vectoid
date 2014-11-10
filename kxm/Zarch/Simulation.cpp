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
#include <kxm/Zarch/GameLogic/GameLogic.h>
#include <kxm/Zarch/Physics/Physics.h>
#include <kxm/Zarch/Events/FrameTimeEvent.h>
#include <kxm/Zarch/Events/ControlsStateEvent.h>


using namespace std;
using namespace std::chrono;
using namespace kxm::Core;
using namespace kxm::Game;


namespace kxm {
namespace Zarch {

Simulation::Simulation(shared_ptr<ThreadCouplingBuffer> presentationCouplingBuffer,
                       int sendToPresentationDirection)
        : processes_(new Processes<ZarchProcess::ProcessType>()),
          processContext_(*processes_, oldEventQueue_),
          presentationCouplingBuffer_(presentationCouplingBuffer),
          sendToPresentationDirection_(sendToPresentationDirection),
          lastFrameTime_(steady_clock::now()) {
    Zarch::RegisterEvents(&eventQueue_);
    
    physics_ = shared_ptr<Physics>(new Physics(processes_));
    eventQueue_.AddHandler(FrameTimeEvent::type, physics_);
    eventQueue_.AddHandler(ControlsStateEvent::type, physics_);
    
    gameLogic_ = shared_ptr<GameLogic>(new GameLogic());
    eventQueue_.AddHandler(ControlsStateEvent::type, gameLogic_);

    Zarch::RegisterEvents(&oldEventQueue_);
    oldEventQueue_.RegisterEventHandler(OldZarchEvent::FrameTimeEvent, physics_);
    oldEventQueue_.RegisterEventHandler(OldZarchEvent::ControlsStateEvent, physics_);
    oldEventQueue_.RegisterEventHandler(OldZarchEvent::ControlsStateEvent, gameLogic_);
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
            
            oldEventQueue_.SerializeScheduledEvents(&accessor.SendBuffer());
            Buffer &receiveBuffer = accessor.ReceiveBuffer();
            oldEventQueue_.DeserializeAndScheduleEvents(receiveBuffer);
            receiveBuffer.Clear();
        }
        oldEventQueue_.ProcessEvents();
        processes_->ExecuteProcesses(processContext_);
    }
    
    puts("simulation thread terminating");
}

void Simulation::GenerateTimeEvent() {
    auto now = steady_clock::now();
    int milliSeconds = (int)duration_cast<milliseconds>(now - lastFrameTime_).count();
    lastFrameTime_ = now;
    float frameDeltaTimeS = (float)milliSeconds / 1000.0f;
    processContext_.eventQueue
                   .ScheduleEvent<OldEvent<Variant>>(OldZarchEvent::FrameTimeEvent).Data()
                   .Reset(frameDeltaTimeS);
}

}
}

