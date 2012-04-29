//
//  TaskList.cpp
//  kxm
//
//  Created by Kai Hergenroether on 4/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#include <kxm/Game/TaskList.h>

using std::vector;
using boost::shared_ptr;


namespace kxm {
namespace Game {

TaskList::TaskList() {
}

void TaskList::Add(shared_ptr<TaskInterface> task) {
    children_.push_back(task);
}

void TaskList::Execute() {
    for (vector<shared_ptr<TaskInterface> >::iterator iter  = children_.begin();
         iter                                              != children_.end();
         ++iter)
        (*iter)->Execute();
}


}    // Namespace Game.
}    // Namespace kxm.
