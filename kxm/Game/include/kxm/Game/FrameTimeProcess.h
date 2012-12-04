//
//  FrameTimeProcess.h
//  kxm
//
//  Created by Kai Hergenroether on 5/6/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#ifndef KXM_GAME_FRAMETIMEPROCESS_H_
#define KXM_GAME_FRAMETIMEPROCESS_H_


#include <boost/shared_ptr.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>

#include <kxm/Game/Process.h>


namespace kxm {
namespace Game {

//! Queries the system time once per frame and centrally maintains time information.
/*!
 *  \ingroup Game
 */
class FrameTimeProcess : public Process {
  public:
    //! Holds time information for a given frame.
    struct FrameTimeInfo {
        FrameTimeInfo() : timeSinceLastFrame(0.0f) {}
        //! In seconds.
        float timeSinceLastFrame;
    };
    
    FrameTimeProcess();
    
    //! Grants read-only access to the frame time info maintained by the task.
    boost::shared_ptr<const FrameTimeInfo> TimeInfo();
    bool Execute(const Process::Context &context);
    
  private:
    FrameTimeProcess(const FrameTimeProcess &other);
    FrameTimeProcess &operator=(const FrameTimeProcess &other);
    
    boost::posix_time::ptime         lastFrameTime_;
    boost::shared_ptr<FrameTimeInfo> timeInfo_;
};


}    // Namespace Game.
}    // Namespace kxm.


#endif    // KXM_GAME_FRAMETIMEPROCESS_H_
