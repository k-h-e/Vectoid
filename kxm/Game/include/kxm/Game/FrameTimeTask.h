//
//  FrameTimeTask.h
//  kxm
//
//  Created by Kai Hergenroether on 5/6/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#ifndef KXM_GAME_FRAMETIMETASK_H_
#define KXM_GAME_FRAMETIMETASK_H_


#include <boost/shared_ptr.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>

#include <kxm/Game/Task.h>


namespace kxm {
namespace Game {

//! Queries the system time once per frame and centrally maintains time information.
/*!
 *  \ingroup Game
 */
class FrameTimeTask : public virtual Task {
  public:
    //! Holds time information for a given frame.
    struct FrameTimeInfo {
        //! In seconds.
        float timeSinceLastFrame;
    };
    
    FrameTimeTask();
    
    //! Grants read-only access to the frame time info maintained by the task.
    boost::shared_ptr<const FrameTimeInfo> TimeInfo();
    bool Execute();
    
  private:
    FrameTimeTask(const FrameTimeTask &other);
    FrameTimeTask &operator=(const FrameTimeTask &other);
    
    boost::posix_time::ptime         lastFrameTime_;
    boost::shared_ptr<FrameTimeInfo> timeInfo_;
};


}    // Namespace Game.
}    // Namespace kxm.


#endif    // KXM_GAME_FRAMETIMETASK_H_
