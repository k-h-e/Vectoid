//
//  Presentation.cpp
//  kxm
//
//  Created by Kai Hergenröther on 4/7/13.
//
//


#include <Zarch/Presentation.h>

#include <kxm/Core/logging.h>
#include <Game/EventQueue.h>
#include <Game/Processes.h>
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
        : eventQueue_(new EventQueue<ZarchEvent, EventHandlerCore>(EventQueueHub::initialBufferSize,
                                                                   eventQueueHub, false)),
          processes_(new Processes()) {
    Zarch::RegisterEvents(eventQueue_.get());
    
    video_ = shared_ptr<Video>(new Video(eventQueue_, processes_));
    for (Event::EventType eventType : video_->EnumerateHandledEvents()) {
        eventQueue_->RegisterHandler(eventType, video_.get());
    }
}

Presentation::~Presentation() {
    eventQueue_->UnregisterHandler(video_.get());
    processes_->UnregisterProcesses(video_.get());
}

void Presentation::PrepareFrame(const ControlsState &controlsState) {
    // We want the next simulation iteration to use the most current controls data, so we schedule
    // the respective event here...
    eventQueue_->Schedule(ControlsStateEvent(controlsState));
    eventQueue_->ProcessEvents();
    processes_->ExecuteProcesses();
}

}
}

