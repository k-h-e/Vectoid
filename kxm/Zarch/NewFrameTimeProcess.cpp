//
//  FrameTimeProcess.cpp
//  kxm
//
//  Created by Kai Hergenroether on 5/6/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#include <kxm/Zarch/NewFrameTimeProcess.h>

#include <kxm/Game/EventQueue.h>
#include <kxm/Zarch/processes.h>


using namespace boost;
using namespace boost::posix_time;
using namespace kxm::Game;


namespace kxm {
namespace Zarch {
 
NewFrameTimeProcess::NewFrameTimeProcess()
        : lastFrameTime_(microsec_clock::local_time()) {
}

bool NewFrameTimeProcess::Execute(const Process::Context &context) {
    ptime now = microsec_clock::local_time();
    int milliSeconds = (int)((now - lastFrameTime_).total_milliseconds());
    lastFrameTime_ = now;
    
    float timeSinceLastFrame = (float)milliSeconds / 1000.0f;
    Event &event = static_cast<const ZarchProcess::Context &>(context)
                       .eventQueue.ScheduleEvent(ZarchEvent::FrameTimeEvent);
    static_cast<VariantEvent &>(event).Reset(timeSinceLastFrame);
    
    return true;
}

}    // Namespace Game.
}    // Namespace kxm.