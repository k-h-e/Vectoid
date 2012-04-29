//
//  TaskList.h
//  kxm
//
//  Created by Kai Hergenroether on 4/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#ifndef KXM_GAME_TASKLIST_H_
#define KXM_GAME_TASKLIST_H_


#include <vector>

#include <boost/shared_ptr.hpp>

#include <kxm/Game/TaskInterface.h>


namespace kxm {
namespace Game {

//! Task grouping together a set of sub-tasks that get executed in defined sequential order.
/*!
 *  \ingroup Game
 */
class TaskList : public virtual TaskInterface {
  public:
    TaskList();
    
    void Add(boost::shared_ptr<TaskInterface> task);
    void Execute();
    
  private:
    TaskList(const TaskList &other);
    TaskList &operator=(const TaskList &other);
    
    std::vector<boost::shared_ptr<TaskInterface> > children_;
};


}    // Namespace Games.
}    // Namespace kxm.


#endif    // KXM_GAME_TASKLIST_H_
