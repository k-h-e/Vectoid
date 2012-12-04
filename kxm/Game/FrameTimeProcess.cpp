//
//  FrameTimeProcess.cpp
//  kxm
//
//  Created by Kai Hergenroether on 5/6/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#include <kxm/Game/FrameTimeProcess.h>

using namespace boost;
using namespace boost::posix_time;


namespace kxm {
namespace Game {
 
FrameTimeProcess::FrameTimeProcess()
        : lastFrameTime_(microsec_clock::local_time()),
          timeInfo_(new FrameTimeInfo()) {
}

shared_ptr<const FrameTimeProcess::FrameTimeInfo> FrameTimeProcess::TimeInfo() {
    return timeInfo_;
}

bool FrameTimeProcess::Execute(const Process::Context &context) {
    ptime now = microsec_clock::local_time();
    int milliSeconds = (int)((now - lastFrameTime_).total_milliseconds());
    timeInfo_->timeSinceLastFrame = (float)milliSeconds / 1000.0f;
    lastFrameTime_ = now;
    return true;
}

}    // Namespace Game.
}    // Namespace kxm.
