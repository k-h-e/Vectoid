//
//  Process.h
//  kxm
//
//  Created by Kai Hergenroether on 4/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#ifndef KXM_GAME_PROCESS_H_
#define KXM_GAME_PROCESS_H_


#include <kxm/Core/Interface.h>


namespace kxm {
namespace Game {

//! A process is an ongoing activity that periodically gets called, e.g. for each frame. It takes
//! part in a co-operative scheduling scheme managed by \ref Processes.
/*!
 *  \ingroup Game
 */
class Process : public virtual Core::Interface {
  public:
    Process();
    //! Executes the process until it co-operatively yields (by returning).
    /*!
     *  \return <c>false</c> in case the process has finished and wishes to be deregistered.
     */
    virtual bool Execute();
    
  private:
    friend class ProcessesCore;
    int     type_;
    Process *next_, *prev_;
};

}    // Namespace Game.
}    // Namespace kxm.


#endif    // KXM_GAME_PROCESS_H_