//
//  Task.h
//  kxm
//
//  Created by Kai Hergenroether on 4/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#ifndef KXM_GAME_TASKINTERFACE_H_
#define KXM_GAME_TASKINTERFACE_H_


#include <kxm/Core/Interface.h>

/*!
 *  \defgroup Game Game Engine
 */


namespace kxm {
namespace Game {

//! Interface to entities that get called once per frame so they can perform a specific task.
/*!
 *  \ingroup Game
 */
class TaskInterface : public virtual Core::Interface {
  public:
    //! Executes the task for the current frame.
    virtual void Execute() = 0;
};


}    // Namespace Game.
}    // Namespace kxm.


#endif    // KXM_GAME_TASKINTERFACE_H_
