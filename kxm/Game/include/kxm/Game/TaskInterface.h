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

//! Ongoing activity that periodically gets called to perform a specific task. Takes part in a
//! co-operative scheduling scheme managed by a \ref Tasks collection.
/*!
 *  \ingroup Game
 */
class TaskInterface : public virtual Core::Interface {
  public:
    //! Indicates that no re-use is desired.
    static const int NoReuseGroup = -1;
    
    //! Executes the task until it co-operatively yields (by returning).
    /*!
     *  \return <c>false</c> in case the task has finished and wishes to be deregistered.
     */
    virtual bool Execute() = 0;
    //! Returns the \ref Tasks group used for re-using tasks of this type, or \ref NoReuseGroup in
    //! case the task does not wish to be re-used.
    virtual int ReuseGroup() = 0;
    //! If you wish the task object to be re-used after it has finished, specify the appropriate
    //! re-use group. By saying \ref NoReuseGroup you can disable re-using (default).
    virtual void SetReuseGroup(int reuseGroup) = 0;
};


}    // Namespace Game.
}    // Namespace kxm.


#endif    // KXM_GAME_TASKINTERFACE_H_
