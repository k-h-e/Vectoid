//
//  FrameTimeProcess.h
//  kxm
//
//  Created by Kai Hergenroether on 5/6/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#ifndef KXM_GAME_NEW_FRAMETIMEPROCESS_H_
#define KXM_GAME_NEW_FRAMETIMEPROCESS_H_


#include <boost/shared_ptr.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>

#include <kxm/Game/Process.h>


namespace kxm {
namespace Zarch {

//! Queries the system time once per frame and generates a time event.
/*!
 *  \ingroup Zarch
 */
class NewFrameTimeProcess : public Game::Process {
  public:
    NewFrameTimeProcess();
    //! (Re)implemented.
    bool Execute(const Process::Context &context);
    
  private:
    NewFrameTimeProcess(const NewFrameTimeProcess &other);
    NewFrameTimeProcess &operator=(const NewFrameTimeProcess &other);
    
    boost::posix_time::ptime lastFrameTime_;
};


}    // Namespace Game.
}    // Namespace kxm.


#endif    // KXM_GAME_FRAMETIMEPROCESS_H_
